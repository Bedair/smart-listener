
#include <float.h>
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

// Model to use
#include <models/model.h>

// Desired sample rate. Typical values: 8/16/22.05/32/44.1/48 kHz
#define SAMPLE_RATE_HZ				16000

// Audio subsystem clock. Typical values depends on the desire sample rate:
// - 8/16/48kHz    : 24.576 MHz
// - 22.05/44.1kHz : 22.579 MHz
#define AUDIO_SYS_CLOCK_HZ          24576000

// Decimation rate of the PDM/PCM block. Typical value is 64
#define DECIMATION_RATE             64

// Microphone sensitivity
// PGA in 0.5 dB increment, for example a value of 5 would mean +2.5 dB.
#define MICROPHONE_GAIN				19

// Multiplication factor of the input signal.
// This should be 1. Any higher value will have an negative impact on the sampling dynamic range.
// However, it can be used as a last resort when MICROPHONE_GAIN is at maximum.
#define DIGITAL_BOOST_FACTOR			10.0f

// Specifies the dynamic range in bits.
// PCM word length, see the A/D specific documentation for valid ranges.
#define AUIDO_BITS_PER_SAMPLE		16

// PDM/PCM Pins
#define PDM_DATA                    P10_5
#define PDM_CLK                     P10_4

// Size of audio buffer
#define AUDIO_BUFFER_SIZE			512

// Converts given audio sample into range [-1,1]
#define SAMPLE_NORMALIZE(sample) 		(((float) (sample)) / (float) (1 << (AUIDO_BITS_PER_SAMPLE - 1)))

// Local functions
static void init_board(void);
static void init_audio(cyhal_pdm_pcm_t* pdm_pcm);
// static void print_model_output(float *src, size_t count);
static void halt_error(int code);

// Imagimob compatibility defines to support all versions of code generation APIs
#ifndef IMAI_RET_ERROR // If not defined, model is generated using older (Imagimob Natrix) code gen API
#define IMAI_NATRIX_API // Use old (Imagimob Natrix) code gen API
#define IMAI_RET_ERROR -2
#define IMAI_RET_STREAMEND -3
#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3
#ifndef IMAI_DATA_OUT_SYMBOLS
    #define IMAI_DATA_OUT_SYMBOLS IMAI_SYMBOL_MAP
#endif
#endif
// End Imagimob compatibility defines

int main(void)
{
	int16_t audio_buffer[AUDIO_BUFFER_SIZE] = {0};
    float label_scores[IMAI_DATA_OUT_COUNT];
    char *label_text[] = IMAI_DATA_OUT_SYMBOLS;

 	size_t audio_count;
 	cyhal_pdm_pcm_t pdm_pcm;

 	// Basic board setup
 	init_board();

    // Initialize model
#ifdef IMAI_NATRIX_API
    IMAI_init();
#else
    halt_error(IMAI_init()); // new api returns status code from init call
#endif


    // Initialize audio sampling
    init_audio(&pdm_pcm);

    // ANSI ESC sequence for clear screen
	printf("\x1b[2J\x1b[;H");

    for (;;)
    {
    	// Move cursor home
    	 printf("\033[H");
    	 printf("Imagimob Audio Model Example\r\n\n");

    	// Read either audio_in_count samples or the number of samples that are currently
    	// available in the receive buffer, whichever is less
    	audio_count = AUDIO_BUFFER_SIZE;
    	memset(audio_buffer, 0, AUDIO_BUFFER_SIZE * sizeof(uint16_t));
    	halt_error(cyhal_pdm_pcm_read(&pdm_pcm, (void *) audio_buffer, &audio_count));

    	float sample_max = 0;
    	for(int i = 0; i < audio_count; i++)
    	{
    		// Convert integer sample to float and pass it to the model
    		float sample = SAMPLE_NORMALIZE(audio_buffer[i]) * DIGITAL_BOOST_FACTOR;
    		halt_error(IMAI_enqueue(&sample));

    		// Used to tune gain control. sample_max should be near 1.0 when shouting directly into the microphone
    		float sample_abs = fabs(sample);
    		if(sample_abs > sample_max)
    			sample_max = sample_abs;

    		// Check if there is any model output to process
    		int16_t best_label = 0;
    		float max_score = -1000.0f;
    		switch(IMAI_dequeue(label_scores))
    		{
    			case IMAI_RET_SUCCESS:		// We have data, display it

    				for(int i = 0; i < IMAI_DATA_OUT_COUNT; i++)
					{
						printf("label: %-10s: score: %f\r\n", label_text[i], label_scores[i]);
						if (label_scores[i] > max_score)
						{
							max_score = label_scores[i];
							best_label = i;
						}
					}

    				printf("\r\n");
    				printf("Output: %-30s\r\n", label_text[best_label]);

    				printf("\r\n");
    				printf("Volume: %.4f\r\n", sample_max);
    				printf("Audio buffer utilization: %.3f\r\n", audio_count / (float)AUDIO_BUFFER_SIZE);

    				break;
    			case IMAI_RET_NODATA:	// No new output, continue with sampling
    				break;
    			case IMAI_RET_ERROR:	// Abort on error 
    				halt_error(IMAI_RET_ERROR);
    				break;
    		}
    	}
    }
}

static void init_board(void)
{
   // Clear watchdog timer so that it doesn't trigger a reset
	#if defined (CY_DEVICE_SECURE)
	    cyhal_wdt_t wdt_obj;
	    result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
	    CY_ASSERT(CY_RSLT_SUCCESS == result);
	    cyhal_wdt_free(&wdt_obj);
	#endif

	// Initialize the device and board peripherals
	halt_error(cybsp_init());

	// Enable global interrupts
	__enable_irq();

	// Initialize retarget-io to use the debug UART port
	halt_error(cy_retarget_io_init_fc(
			CYBSP_DEBUG_UART_TX,
			CYBSP_DEBUG_UART_RX,
			CYBSP_DEBUG_UART_CTS,
			CYBSP_DEBUG_UART_RTS,
			CY_RETARGET_IO_BAUDRATE));
}

static void init_audio(cyhal_pdm_pcm_t* pdm_pcm)
{
	cyhal_clock_t audio_clock;
	cyhal_clock_t pll_clock;

	const cyhal_pdm_pcm_cfg_t pdm_pcm_cfg =
	{
		.sample_rate     = SAMPLE_RATE_HZ,				// Sample rate in Hz
		.decimation_rate = DECIMATION_RATE,				// Decimation Rate of the PDM/PCM block
		.mode            = CYHAL_PDM_PCM_MODE_LEFT,		// Microphone to use (Channel)
		.word_length     = AUIDO_BITS_PER_SAMPLE,  		// Bits per sample
		.left_gain       = MICROPHONE_GAIN,   			// Left channel gain dB ("volume")
		.right_gain      = MICROPHONE_GAIN,   			// Right channel gain dB ("volume")
	};

	// Initialize the PLL
	halt_error(cyhal_clock_reserve(&pll_clock, &CYHAL_CLOCK_PLL[0]));
	halt_error(cyhal_clock_set_frequency(&pll_clock, AUDIO_SYS_CLOCK_HZ, NULL));
	halt_error(cyhal_clock_set_enabled(&pll_clock, true, true));

	// Initialize the audio subsystem clock (CLK_HF[1])
	// The CLK_HF[1] is the root clock for the I2S and PDM/PCM blocks
	halt_error(cyhal_clock_reserve(&audio_clock, &CYHAL_CLOCK_HF[1]));

	// Source the audio subsystem clock from PLL
	halt_error(cyhal_clock_set_source(&audio_clock, &pll_clock));
	halt_error(cyhal_clock_set_enabled(&audio_clock, true, true));

	// Initialize the pulse-density modulation to pulse-code modulation (PDM/PCM) converter.
	halt_error(cyhal_pdm_pcm_init(pdm_pcm, PDM_DATA, PDM_CLK, &audio_clock, &pdm_pcm_cfg));

	// Clear PDM/PCM RX FIFO
	halt_error(cyhal_pdm_pcm_clear(pdm_pcm));

	// Start PDM/PCM
	halt_error(cyhal_pdm_pcm_start(pdm_pcm));
}

// Halt execution and flash LED with the given code.
// If the given code is 0 (for success) this function does nothing.
static void halt_error(int code)
{
	if(code == 0) // Universal success code
		return;

	// flash code on LED?
	for(;;){}
}

/* EOF */

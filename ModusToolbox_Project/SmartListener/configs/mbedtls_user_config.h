/**
 * \file config.h
 *
 * \brief Configuration options (set of defines)
 *
 *  This set of compile-time options may be used to enable
 *  or disable features selectively, and reduce the global
 *  memory footprint.
 */
/*
 *  Copyright (C) 2006-2018, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#ifndef MBEDTLS_USER_CONFIG_HEADER
#define MBEDTLS_USER_CONFIG_HEADER

#if !defined(COMPONENT_4390X)
#include "cy_syslib.h"
#endif

/**
 * Compiling Mbed TLS for Cortex-M0/0+/1/M23 cores with optimization enabled and on ARMC6 compiler results in errors.
 * These cores lack the required full Thumb-2 support, causing the inline assembly to require more registers than available.
 * The workaround is to use 'MULADDC_CANNOT_USE_R7' compilation flag, or without optimization flag,
 * but note that this will compile without the assmebly optimization.
 *
 * To read more about this issue, refer to https://github.com/ARMmbed/mbed-os/pull/14529/commits/86e7bc559b0d1a055bf84ea9249763d2349fb6e8
 */

#if defined(COMPONENT_CM0P) && defined(COMPONENT_ARM)
#define MULADDC_CANNOT_USE_R7
#endif

/* Currently there is a bug with MBEDTLS 3.4.0 compilation with IAR compiler when assembly instructions are enabled. Hence
 * disabling assembly instructions for IAR. This will be fixed in future MBEDTLS releases.
 */
#if defined (__IAR_SYSTEMS_ICC__)
#undef MBEDTLS_HAVE_ASM
#endif

/**
 * \def MBEDTLS_HAVE_TIME_DATE
 *
 * System has time.h, time(), and an implementation for
 * mbedtls_platform_gmtime_r() (see below).
 * The time needs to be correct (not necessarily very accurate, but at least
 * the date should be correct). This is used to verify the validity period of
 * X.509 certificates.
 *
 * Comment if your system does not have a correct clock.
 *
 * \note mbedtls_platform_gmtime_r() is an abstraction in platform_util.h that
 * behaves similarly to the gmtime_r() function from the C standard. Refer to
 * the documentation for mbedtls_platform_gmtime_r() for more information.
 *
 * \note It is possible to configure an implementation for
 * mbedtls_platform_gmtime_r() at compile-time by using the macro
 * MBEDTLS_PLATFORM_GMTIME_R_ALT.
 */
#undef MBEDTLS_HAVE_TIME_DATE


/**
 * \def MBEDTLS_PLATFORM_EXIT_ALT
 *
 * MBEDTLS_PLATFORM_XXX_ALT: Uncomment a macro to let mbed TLS support the
 * function in the platform abstraction layer.
 *
 * Example: In case you uncomment MBEDTLS_PLATFORM_PRINTF_ALT, mbed TLS will
 * provide a function "mbedtls_platform_set_printf()" that allows you to set an
 * alternative printf function pointer.
 *
 * All these define require MBEDTLS_PLATFORM_C to be defined!
 *
 * \note MBEDTLS_PLATFORM_SNPRINTF_ALT is required on Windows;
 * it will be enabled automatically by check_config.h
 *
 * \warning MBEDTLS_PLATFORM_XXX_ALT cannot be defined at the same time as
 * MBEDTLS_PLATFORM_XXX_MACRO!
 *
 * Requires: MBEDTLS_PLATFORM_TIME_ALT requires MBEDTLS_HAVE_TIME
 *
 * Uncomment a macro to enable alternate implementation of specific base
 * platform function
 */
// #define MBEDTLS_PLATFORM_EXIT_ALT
#define MBEDTLS_PLATFORM_TIME_ALT
// #define MBEDTLS_PLATFORM_FPRINTF_ALT
// #define MBEDTLS_PLATFORM_PRINTF_ALT
// #define MBEDTLS_PLATFORM_SNPRINTF_ALT
// #define MBEDTLS_PLATFORM_NV_SEED_ALT
// #define MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT

/**
 * \def MBEDTLS_ENTROPY_HARDWARE_ALT
 *
 * Uncomment this macro to let mbed TLS use your own implementation of a
 * hardware entropy collector.
 *
 * Your function must be called \c mbedtls_hardware_poll(), have the same
 * prototype as declared in entropy_poll.h, and accept NULL as first argument.
 *
 * Uncomment to use your own hardware entropy collector.
 */
#define MBEDTLS_ENTROPY_HARDWARE_ALT
/**
 * \def MBEDTLS_ECP_DP_SECP192R1_ENABLED
 *
 * MBEDTLS_ECP_XXXX_ENABLED: Enables specific curves within the Elliptic Curve
 * module.  By default all supported curves are enabled.
 *
 * Comment macros to disable the curve and functions for it
 */
#undef MBEDTLS_ECP_DP_SECP192R1_ENABLED
#undef MBEDTLS_ECP_DP_SECP224R1_ENABLED
// #define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#undef MBEDTLS_ECP_DP_SECP384R1_ENABLED
#undef MBEDTLS_ECP_DP_SECP521R1_ENABLED
#undef MBEDTLS_ECP_DP_SECP192K1_ENABLED
#undef MBEDTLS_ECP_DP_SECP224K1_ENABLED
#undef MBEDTLS_ECP_DP_SECP256K1_ENABLED
#undef MBEDTLS_ECP_DP_BP256R1_ENABLED
#undef MBEDTLS_ECP_DP_BP384R1_ENABLED
#undef MBEDTLS_ECP_DP_BP512R1_ENABLED
// #undef MBEDTLS_ECP_DP_CURVE25519_ENABLED
#undef MBEDTLS_ECP_DP_CURVE448_ENABLED

/**
 * \def MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
 *
 * Enable the PSK based ciphersuite modes in SSL / TLS.
 *
 * This enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDTLS_TLS_PSK_WITH_AES_256_GCM_SHA384
 *      MBEDTLS_TLS_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDTLS_TLS_PSK_WITH_AES_256_CBC_SHA
 *      MBEDTLS_TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDTLS_TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDTLS_TLS_PSK_WITH_AES_128_GCM_SHA256
 *      MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA
 *      MBEDTLS_TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDTLS_TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDTLS_TLS_PSK_WITH_3DES_EDE_CBC_SHA
 *      MBEDTLS_TLS_PSK_WITH_RC4_128_SHA
 */
#undef MBEDTLS_KEY_EXCHANGE_PSK_ENABLED


/**
 * \def MBEDTLS_PK_PARSE_EC_EXTENDED
 *
 * Enhance support for reading EC keys using variants of SEC1 not allowed by
 * RFC 5915 and RFC 5480.
 *
 * Currently this means parsing the SpecifiedECDomain choice of EC
 * parameters (only known groups are supported, not arbitrary domains, to
 * avoid validation issues).
 *
 * Disable if you only need to support RFC 5915 + 5480 key formats.
 */
#undef MBEDTLS_PK_PARSE_EC_EXTENDED


#undef MBEDTLS_FS_IO


/**
 * \def MBEDTLS_NO_PLATFORM_ENTROPY
 *
 * Do not use built-in platform entropy functions.
 * This is useful if your platform does not support
 * standards like the /dev/urandom or Windows CryptoAPI.
 *
 * Uncomment this macro to disable the built-in platform entropy functions.
 */
#define MBEDTLS_NO_PLATFORM_ENTROPY

/**
 * \def MBEDTLS_ENTROPY_FORCE_SHA256
 *
 * Force the entropy accumulator to use a SHA-256 accumulator instead of the
 * default SHA-512 based one (if both are available).
 *
 * Requires: MBEDTLS_SHA256_C
 *
 * On 32-bit systems SHA-256 can be much faster than SHA-512. Use this option
 * if you have performance concerns.
 *
 * This option is only useful if both MBEDTLS_SHA256_C and
 * MBEDTLS_SHA512_C are defined. Otherwise the available hash module is used.
 */
#define MBEDTLS_ENTROPY_FORCE_SHA256

/*
 * \def MBEDTLS_SSL_SRV_C
 *
 * Enables server option in device
 *
 * Comment this macro to support server
 */
#undef MBEDTLS_SSL_SRV_C
/*
 * \def MBEDTLS_CHACHA20_C
 * \def MBEDTLS_CHACHAPOLY_C
 * \def MBEDTLS_POLY1305_C
 *
 * Enable support of CHACHA20 and CHACHAPOLY algorithm.
 */
#undef MBEDTLS_CHACHA20_C

#undef MBEDTLS_CHACHAPOLY_C

#undef MBEDTLS_POLY1305_C

/*
 * \def MBEDTLS_CAMELLIA_C
 *
 * Enable to support camellia cipher suites.
 */
#undef MBEDTLS_CAMELLIA_C


/**
 * \def MBEDTLS_SELF_TEST
 *
 * Enable the checkup functions (*_self_test).
 */
#undef MBEDTLS_SELF_TEST

/**
 * \def MBEDTLS_SSL_FALLBACK_SCSV
 *
 * Enable support for FALLBACK_SCSV (draft-ietf-tls-downgrade-scsv-00).
 *
 * For servers, it is recommended to always enable this, unless you support
 * only one version of TLS, or know for sure that none of your clients
 * implements a fallback strategy.
 *
 * For clients, you only need this if you're using a fallback strategy, which
 * is not recommended in the first place, unless you absolutely need it to
 * interoperate with buggy (version-intolerant) servers.
 *
 * Comment this macro to disable support for FALLBACK_SCSV
 */
#undef MBEDTLS_SSL_FALLBACK_SCSV

/**
 * \def MBEDTLS_SSL_CBC_RECORD_SPLITTING
 *
 * Enable 1/n-1 record splitting for CBC mode in SSLv3 and TLS 1.0.
 *
 * This is a countermeasure to the BEAST attack, which also minimizes the risk
 * of interoperability issues compared to sending 0-length records.
 *
 * Comment this macro to disable 1/n-1 record splitting.
 */
#undef MBEDTLS_SSL_CBC_RECORD_SPLITTING

/**
 * \def MBEDTLS_SSL_RENEGOTIATION
 *
 * Enable support for TLS renegotiation.
 *
 * The two main uses of renegotiation are (1) refresh keys on long-lived
 * connections and (2) client authentication after the initial handshake.
 * If you don't need renegotiation, it's probably better to disable it, since
 * it has been associated with security issues in the past and is easy to
 * misuse/misunderstand.
 *
 * Comment this to disable support for renegotiation.
 *
 * \note   Even if this option is disabled, both client and server are aware
 *         of the Renegotiation Indication Extension (RFC 5746) used to
 *         prevent the SSL renegotiation attack (see RFC 5746 Sect. 1).
 *         (See \c mbedtls_ssl_conf_legacy_renegotiation for the
 *          configuration of this extension).
 *
 */
#undef MBEDTLS_SSL_RENEGOTIATION

/**
 * \def MBEDTLS_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO
 *
 * Enable support for receiving and parsing SSLv2 Client Hello messages for the
 * SSL Server module (MBEDTLS_SSL_SRV_C).
 *
 * Uncomment this macro to enable support for SSLv2 Client Hello messages.
 */
// #define MBEDTLS_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO

/**
 * \def MBEDTLS_SSL_PROTO_TLS1
 *
 * Enable support for TLS 1.0.
 *
 * Requires: MBEDTLS_MD5_C
 *           MBEDTLS_SHA1_C
 *
 * Comment this macro to disable support for TLS 1.0
 */
#undef MBEDTLS_SSL_PROTO_TLS1

/**
 * \def MBEDTLS_SSL_PROTO_TLS1_1
 *
 * Enable support for TLS 1.1 (and DTLS 1.0 if DTLS is enabled).
 *
 * Requires: MBEDTLS_MD5_C
 *           MBEDTLS_SHA1_C
 *
 * Comment this macro to disable support for TLS 1.1 / DTLS 1.0
 */
#undef MBEDTLS_SSL_PROTO_TLS1_1

/**
 * \def MBEDTLS_SSL_PROTO_DTLS
 *
 * Enable support for DTLS (all available versions).
 *
 * Enable this and MBEDTLS_SSL_PROTO_TLS1_1 to enable DTLS 1.0,
 * and/or this and MBEDTLS_SSL_PROTO_TLS1_2 to enable DTLS 1.2.
 *
 * Requires: MBEDTLS_SSL_PROTO_TLS1_1
 *        or MBEDTLS_SSL_PROTO_TLS1_2
 *
 * Comment this macro to disable support for DTLS
 */
#undef MBEDTLS_SSL_PROTO_DTLS

/**
 * \def MBEDTLS_SSL_DTLS_CONNECTION_ID_COMPAT
 *
 * Defines whether RFC 9146 (default) or the legacy version
 * (version draft-ietf-tls-dtls-connection-id-05,
 * https://tools.ietf.org/html/draft-ietf-tls-dtls-connection-id-05)
 * is used.
 *
 * Set the value to 0 for the standard version, and
 * 1 for the legacy draft version.
 *
 * \deprecated Support for the legacy version of the DTLS
 *             Connection ID feature is deprecated. Please
 *             switch to the standardized version defined
 *             in RFC 9146 enabled by utilizing
 *             MBEDTLS_SSL_DTLS_CONNECTION_ID without use
 *             of MBEDTLS_SSL_DTLS_CONNECTION_ID_COMPAT.
 *
 * Requires: MBEDTLS_SSL_DTLS_CONNECTION_ID
 */
#undef MBEDTLS_SSL_DTLS_CONNECTION_ID_COMPAT

/**
 * \def MBEDTLS_SSL_DTLS_CONNECTION_ID
 *
 * Enable support for the DTLS Connection ID (CID) extension,
 * which allows to identify DTLS connections across changes
 * in the underlying transport. The CID functionality is described
 * in RFC 9146.
 *
 * Setting this option enables the SSL APIs `mbedtls_ssl_set_cid()`,
 * mbedtls_ssl_get_own_cid()`, `mbedtls_ssl_get_peer_cid()` and
 * `mbedtls_ssl_conf_cid()`. See the corresponding documentation for
 * more information.
 *
 * The maximum lengths of outgoing and incoming CIDs can be configured
 * through the options
 * - MBEDTLS_SSL_CID_OUT_LEN_MAX
 * - MBEDTLS_SSL_CID_IN_LEN_MAX.
 *
 * Requires: MBEDTLS_SSL_PROTO_DTLS
 *
 * Uncomment to enable the Connection ID extension.
 */
#undef MBEDTLS_SSL_DTLS_CONNECTION_ID

/**
 * \def MBEDTLS_SSL_DTLS_ANTI_REPLAY
 *
 * Enable support for the anti-replay mechanism in DTLS.
 *
 * Requires: MBEDTLS_SSL_TLS_C
 *           MBEDTLS_SSL_PROTO_DTLS
 *
 * \warning Disabling this is often a security risk!
 * See mbedtls_ssl_conf_dtls_anti_replay() for details.
 *
 * Comment this to disable anti-replay in DTLS.
 */
#undef MBEDTLS_SSL_DTLS_ANTI_REPLAY

/**
 * \def MBEDTLS_SSL_DTLS_HELLO_VERIFY
 *
 * Enable support for HelloVerifyRequest on DTLS servers.
 *
 * This feature is highly recommended to prevent DTLS servers being used as
 * amplifiers in DoS attacks against other hosts. It should always be enabled
 * unless you know for sure amplification cannot be a problem in the
 * environment in which your server operates.
 *
 * \warning Disabling this can ba a security risk! (see above)
 *
 * Requires: MBEDTLS_SSL_PROTO_DTLS
 *
 * Comment this to disable support for HelloVerifyRequest.
 */
#undef MBEDTLS_SSL_DTLS_HELLO_VERIFY

/**
 * \def MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE
 *
 * Enable server-side support for clients that reconnect from the same port.
 *
 * Some clients unexpectedly close the connection and try to reconnect using the
 * same source port. This needs special support from the server to handle the
 * new connection securely, as described in section 4.2.8 of RFC 6347. This
 * flag enables that support.
 *
 * Requires: MBEDTLS_SSL_DTLS_HELLO_VERIFY
 *
 * Comment this to disable support for clients reusing the source port.
 */
#undef MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE

/**
 * \def MBEDTLS_SSL_DTLS_BADMAC_LIMIT
 *
 * Enable support for a limit of records with bad MAC.
 *
 * See mbedtls_ssl_conf_dtls_badmac_limit().
 *
 * Requires: MBEDTLS_SSL_PROTO_DTLS
 */
#undef MBEDTLS_SSL_DTLS_BADMAC_LIMIT

/**
 * \def MBEDTLS_SSL_EXPORT_KEYS
 *
 * Enable support for exporting key block and master secret.
 * This is required for certain users of TLS, e.g. EAP-TLS.
 *
 * Comment this macro to disable support for key export
 */
#undef MBEDTLS_SSL_EXPORT_KEYS


/**
 * \def MBEDTLS_SSL_TRUNCATED_HMAC
 *
 * Enable support for RFC 6066 truncated HMAC in SSL.
 *
 * Comment this macro to disable support for truncated HMAC in SSL
 */
#undef MBEDTLS_SSL_TRUNCATED_HMAC

/**
 * \def MBEDTLS_AESNI_C
 *
 * Enable AES-NI support on x86-64.
 *
 * Module:  library/aesni.c
 * Caller:  library/aes.c
 *
 * Requires: MBEDTLS_HAVE_ASM
 *
 * This modules adds support for the AES-NI instructions on x86-64
 */
#undef MBEDTLS_AESNI_C

/**
 * \def MBEDTLS_NET_C
 *
 * Enable the TCP and UDP over IPv6/IPv4 networking routines.
 *
 * \note This module only works on POSIX/Unix (including Linux, BSD and OS X)
 * and Windows. For other platforms, you'll want to disable it, and write your
 * own networking callbacks to be passed to \c mbedtls_ssl_set_bio().
 *
 * \note See also our Knowledge Base article about porting to a new
 * environment:
 * https://tls.mbed.org/kb/how-to/how-do-i-port-mbed-tls-to-a-new-environment-OS
 *
 * Module:  library/net_sockets.c
 *
 * This module provides networking routines.
 */
#undef MBEDTLS_NET_C

/**
 * \def MBEDTLS_SSL_COOKIE_C
 *
 * Enable basic implementation of DTLS cookies for hello verification.
 *
 * Module:  library/ssl_cookie.c
 * Caller:
 */
#undef MBEDTLS_SSL_COOKIE_C

/**
 * \def MBEDTLS_TIMING_C
 *
 * Enable the semi-portable timing interface.
 *
 * \note The provided implementation only works on POSIX/Unix (including Linux,
 * BSD and OS X) and Windows. On other platforms, you can either disable that
 * module and provide your own implementations of the callbacks needed by
 * \c mbedtls_ssl_set_timer_cb() for DTLS, or leave it enabled and provide
 * your own implementation of the whole module by setting
 * \c MBEDTLS_TIMING_ALT in the current file.
 *
 * \note See also our Knowledge Base article about porting to a new
 * environment:
 * https://tls.mbed.org/kb/how-to/how-do-i-port-mbed-tls-to-a-new-environment-OS
 *
 * Module:  library/timing.c
 * Caller:  library/havege.c
 *
 * This module is used by the HAVEGE random number generator.
 */
#undef MBEDTLS_TIMING_C

/**
 * \def MBEDTLS_X509_CRL_PARSE_C
 *
 * Enable X.509 CRL parsing.
 *
 * Module:  library/x509_crl.c
 * Caller:  library/x509_crt.c
 *
 * Requires: MBEDTLS_X509_USE_C
 *
 * This module is required for X.509 CRL parsing.
 */
#undef MBEDTLS_X509_CRL_PARSE_C

/**
 * \def MBEDTLS_X509_CSR_PARSE_C
 *
 * Enable X.509 Certificate Signing Request (CSR) parsing.
 *
 * Module:  library/x509_csr.c
 * Caller:  library/x509_crt_write.c
 *
 * Requires: MBEDTLS_X509_USE_C
 *
 * This module is used for reading X.509 certificate request.
 */
#undef MBEDTLS_X509_CSR_PARSE_C

/**
 * \def MBEDTLS_X509_CREATE_C
 *
 * Enable X.509 core for creating certificates.
 *
 * Module:  library/x509_create.c
 *
 * Requires: MBEDTLS_BIGNUM_C, MBEDTLS_OID_C, MBEDTLS_PK_WRITE_C
 *
 * This module is the basis for creating X.509 certificates and CSRs.
 */
#undef MBEDTLS_X509_CREATE_C

/**
 * \def MBEDTLS_X509_CSR_WRITE_C
 *
 * Enable creating X.509 Certificate Signing Requests (CSR).
 *
 * Module:  library/x509_csr_write.c
 *
 * Requires: MBEDTLS_X509_CREATE_C
 *
 * This module is required for X.509 certificate request writing.
 */
#undef MBEDTLS_X509_CSR_WRITE_C

/**
 * \def MBEDTLS_X509_CRT_WRITE_C
 *
 * Enable creating X.509 certificates.
 *
 * Module:  library/x509_crt_write.c
 *
 * Requires: MBEDTLS_X509_CREATE_C
 *
 * This module is required for X.509 certificate creation.
 */
#undef MBEDTLS_X509_CRT_WRITE_C

/**
 * \def MBEDTLS_CERTS_C
 *
 * Enable the test certificates.
 *
 * Module:  library/certs.c
 * Caller:
 *
 * This module is used for testing (ssl_client/server).
 */
#undef MBEDTLS_CERTS_C

/**
 * \def MBEDTLS_ERROR_C
 *
 * Enable error code to error string conversion.
 *
 * Module:  library/error.c
 * Caller:
 *
 * This module enables mbedtls_strerror().
 */
#undef MBEDTLS_ERROR_C

/**
 * \def MBEDTLS_PADLOCK_C
 *
 * Enable VIA Padlock support on x86.
 *
 * Module:  library/padlock.c
 * Caller:  library/aes.c
 *
 * Requires: MBEDTLS_HAVE_ASM
 *
 * This modules adds support for the VIA PadLock on x86.
 */
#undef MBEDTLS_PADLOCK_C

/**
 * \def MBEDTLS_RIPEMD160_C
 *
 * Enable the RIPEMD-160 hash algorithm.
 *
 * Module:  library/ripemd160.c
 * Caller:  library/md.c
 *
 */
#undef MBEDTLS_RIPEMD160_C

/**
 * \def MBEDTLS_ARC4_C
 *
 * Enable the ARCFOUR stream cipher.
 *
 * Module:  library/arc4.c
 * Caller:  library/cipher.c
 *
 * This module enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_ECDH_RSA_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_ECDHE_RSA_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_DHE_PSK_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_RSA_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_RSA_WITH_RC4_128_MD5
 *      MBEDTLS_TLS_RSA_PSK_WITH_RC4_128_SHA
 *      MBEDTLS_TLS_PSK_WITH_RC4_128_SHA
 *
 * \warning   ARC4 is considered a weak cipher and its use constitutes a
 *            security risk. If possible, we recommend avoidng dependencies on
 *            it, and considering stronger ciphers instead.
 *
 */
#undef MBEDTLS_ARC4_C

/**
 * \def MBEDTLS_XTEA_C
 *
 * Enable the XTEA block cipher.
 *
 * Module:  library/xtea.c
 * Caller:
 */
#undef MBEDTLS_XTEA_C

/**
 * \def MBEDTLS_BLOWFISH_C
 *
 * Enable the Blowfish block cipher.
 *
 * Module:  library/blowfish.c
 */
#undef MBEDTLS_BLOWFISH_C

/**
 * \def MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
 *
 * Enable the DHE-PSK based ciphersuite modes in SSL / TLS.
 *
 * Requires: MBEDTLS_DHM_C
 *
 * This enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDTLS_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384
 *      MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA
 *      MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDTLS_TLS_DHE_PSK_WITH_AES_128_GCM_SHA256
 *      MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA
 *      MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDTLS_TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDTLS_TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA
 *      MBEDTLS_TLS_DHE_PSK_WITH_RC4_128_SHA
 *
 * \warning    Using DHE constitutes a security risk as it
 *             is not possible to validate custom DH parameters.
 *             If possible, it is recommended users should consider
 *             preferring other methods of key exchange.
 *             See dhm.h for more details.
 *
 */
#undef MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED

/**
 * \def MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
 *
 * Enable the ECDHE-PSK based ciphersuite modes in SSL / TLS.
 *
 * Requires: MBEDTLS_ECDH_C
 *
 * This enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA
 *      MBEDTLS_TLS_ECDHE_PSK_WITH_RC4_128_SHA
 */
#undef MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED

/**
 * \def MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
 *
 * Enable the RSA-PSK based ciphersuite modes in SSL / TLS.
 *
 * Requires: MBEDTLS_RSA_C, MBEDTLS_PKCS1_V15,
 *           MBEDTLS_X509_CRT_PARSE_C
 *
 * This enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDTLS_TLS_RSA_PSK_WITH_AES_256_GCM_SHA384
 *      MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA
 *      MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDTLS_TLS_RSA_PSK_WITH_AES_128_GCM_SHA256
 *      MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA
 *      MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDTLS_TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA
 *      MBEDTLS_TLS_RSA_PSK_WITH_RC4_128_SHA
 */
#undef MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED

/**
 * \def MBEDTLS_PSA_CRYPTO_STORAGE_C
 *
 * Enable the Platform Security Architecture persistent key storage.
 *
 * Module:  library/psa_crypto_storage.c
 *
 * Requires: MBEDTLS_PSA_CRYPTO_C,
 *           either MBEDTLS_PSA_ITS_FILE_C or a native implementation of
 *           the PSA ITS interface
 */
#undef MBEDTLS_PSA_CRYPTO_STORAGE_C

/**
 * \def MBEDTLS_PSA_ITS_FILE_C
 *
 * Enable the emulation of the Platform Security Architecture
 * Internal Trusted Storage (PSA ITS) over files.
 *
 * Module:  library/psa_its_file.c
 *
 * Requires: MBEDTLS_FS_IO
 */
#undef MBEDTLS_PSA_ITS_FILE_C

/**
 * \def MBEDTLS_SSL_PROTO_TLS1_3
 *
 * Enable support for TLS 1.3.
 *
 * \note The support for TLS 1.3 is not comprehensive yet, in particular
 *       pre-shared keys are not supported.
 *       See docs/architecture/tls13-support.md for a description of the TLS
 *       1.3 support that this option enables.
 *
 * Requires: MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
 * Requires: MBEDTLS_PSA_CRYPTO_C
 *
 * \note TLS 1.3 uses PSA crypto for cryptographic operations that are
 *       directly performed by TLS 1.3 code. As a consequence, you must
 *       call psa_crypto_init() before the first TLS 1.3 handshake.
 *
 * \note Cryptographic operations performed indirectly via another module
 *       (X.509, PK) or by code shared with TLS 1.2 (record protection,
 *       running handshake hash) only use PSA crypto if
 *       #MBEDTLS_USE_PSA_CRYPTO is enabled.
 *
 * Uncomment this macro to enable the support for TLS 1.3.
 */
#define MBEDTLS_SSL_PROTO_TLS1_3

#ifndef MBEDTLS_SSL_PROTO_TLS1_3
/**
 * \def MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
 *
 * This option controls the availability of the API mbedtls_ssl_get_peer_cert()
 * giving access to the peer's certificate after completion of the handshake.
 *
 * Unless you need mbedtls_ssl_peer_cert() in your application, it is
 * recommended to disable this option for reduced RAM usage.
 *
 * \note If this option is disabled, mbedtls_ssl_get_peer_cert() is still
 *       defined, but always returns \c NULL.
 *
 * \note This option has no influence on the protection against the
 *       triple handshake attack. Even if it is disabled, Mbed TLS will
 *       still ensure that certificates do not change during renegotiation,
 *       for exaple by keeping a hash of the peer's certificate.
 *
 * Comment this macro to disable storing the peer's certificate
 * after the handshake.
 */
#undef MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#endif

/* MBEDTLS 3.4 version has build error when TLS1.3 is enabled and session ticket flag is not enabled.
 * Hence, enabling session ticket flag when TLS1.3 is enabled though we dont support.
 * Note: User should not disable session ticket flag when TLS1.3 is enabled otherwise it will result into
 *       build error.
 */
#ifndef MBEDTLS_SSL_PROTO_TLS1_3
/**
 * \def MBEDTLS_SSL_SESSION_TICKETS
 *
 * Enable support for RFC 5077 session tickets in SSL.
 * Client-side, provides full support for session tickets (maintenance of a
 * session store remains the responsibility of the application, though).
 * Server-side, you also need to provide callbacks for writing and parsing
 * tickets, including authenticated encryption and key management. Example
 * callbacks are provided by MBEDTLS_SSL_TICKET_C.
 *
 * Comment this macro to disable support for SSL session tickets
 */
#undef MBEDTLS_SSL_SESSION_TICKETS
#endif

#ifdef MBEDTLS_SSL_PROTO_TLS1_3
/**
 * \def MBEDTLS_PK_RSA_ALT_SUPPORT
 *
 * Support external private RSA keys (eg from a HSM) in the PK layer.
 *
 * Comment this macro to disable support for external private RSA keys.
 */
#define MBEDTLS_PK_RSA_ALT_SUPPORT

/**
 * \def MBEDTLS_PSA_CRYPTO_C
 *
 * Enable the Platform Security Architecture cryptography API.
 *
 * \warning The PSA Crypto API is still beta status. While you're welcome to
 * experiment using it, incompatible API changes are still possible, and some
 * parts may not have reached the same quality as the rest of Mbed TLS yet.
 *
 * Module:  library/psa_crypto.c
 *
 * Requires: MBEDTLS_CTR_DRBG_C, MBEDTLS_ENTROPY_C
 *
 */
#define MBEDTLS_PSA_CRYPTO_C

/**
 * \def MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE
 *
 * Enable TLS 1.3 middlebox compatibility mode.
 *
 * As specified in Section D.4 of RFC 8446, TLS 1.3 offers a compatibility
 * mode to make a TLS 1.3 connection more likely to pass through middle boxes
 * expecting TLS 1.2 traffic.
 *
 * Turning on the compatibility mode comes at the cost of a few added bytes
 * on the wire, but it doesn't affect compatibility with TLS 1.3 implementations
 * that don't use it. Therefore, unless transmission bandwidth is critical and
 * you know that middlebox compatibility issues won't occur, it is therefore
 * recommended to set this option.
 *
 * Comment to disable compatibility mode for TLS 1.3. If
 * MBEDTLS_SSL_PROTO_TLS1_3 is not enabled, this option does not have any
 * effect on the build.
 *
 */
#define MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE
#endif

/**
 * \def MBEDTLS_DEPRECATED_REMOVED
 *
 * Remove deprecated functions and features so that they generate an error if
 * used. Functionality deprecated in one version will usually be removed in the
 * next version. You can enable this to help you prepare the transition to a
 * new major version by making sure your code is not using this functionality.
 *
 * Uncomment to get errors on using deprecated functions and features.
 */
#define MBEDTLS_DEPRECATED_REMOVED

/**
 * \def Enable MBEDTLS debug logs & set debug level
 *
 * MBEDTLS_VERBOSE values:
 * 0 No debug      - No logs are printed on console
 * 1 Error         - Error messages are printed on console
 * 2 State change  - State level change logs are printed on console
 * 3 Informational - Informational logs printed on console
 * 4 Verbose       - All the logs are printed on console
 */
#define MBEDTLS_VERBOSE 0

/**
 * \def Comment out below line in addition to setting MBEDTLS_VERBOSE value to get the MBEDTLS logs
 *
 * MBEDTLS_DEBUG_C flag is by default undefined to save code space (~60Kb). For low memory platform, when MBEDTLS_DEBUG_C is enabled
 * make sure to remove unwanted features of MBEDTLS which are not used in the application to avoid code size overflow issues.
 */
#undef MBEDTLS_DEBUG_C

/**
 * \def MBEDTLS_LMS_C
 *
 * Enable the LMS stateful-hash asymmetric signature algorithm.
 *
 * Module:  library/lms.c
 * Caller:
 *
 * Requires: MBEDTLS_PSA_CRYPTO_C
 *
 * Uncomment to enable the LMS verification algorithm and public key operations.
 */
#undef MBEDTLS_LMS_C

/**
 * \def MBEDTLS_PKCS7_C
 *
 * Enable PKCS #7 core for using PKCS #7-formatted signatures.
 * RFC Link - https://tools.ietf.org/html/rfc2315
 *
 * Module:  library/pkcs7.c
 *
 * Requires: MBEDTLS_ASN1_PARSE_C, MBEDTLS_OID_C, MBEDTLS_PK_PARSE_C,
 *           MBEDTLS_X509_CRT_PARSE_C MBEDTLS_X509_CRL_PARSE_C,
 *           MBEDTLS_BIGNUM_C, MBEDTLS_MD_C
 *
 * This module is required for the PKCS #7 parsing modules.
 */
#undef MBEDTLS_PKCS7_C

/* When TLS1.3 and TLS1.2 both are enabled, there is no version negotiation currently supported for server. Hence, when both
 * are enabled, the below macro can be changed to force the TLS version to be used on server side. Please note that this macro
 * is only used when device is acting as a server. for client, version negotiation is supported.
 */
#define FORCE_TLS_VERSION MBEDTLS_SSL_VERSION_TLS1_3

/**
 * \def Enable alternate crypto implementations to use the hardware
 *      acceleration. Include The hardware acceleration module's (cy-mbedtls-acceleration)
 *      header file to enable the supported ALT configurations.
 */
#ifndef DISABLE_MBEDTLS_ACCELERATION
#include "mbedtls_alt_config.h"

/* MBEDTLS defines for Dcache supported platforms */
#if !defined (CY_DISABLE_XMC7000_DATA_CACHE) && defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
/**
 * \def MBEDTLS_PLATFORM_MEMORY
 *
 * Enable the memory allocation layer.
 *
 * By default mbed TLS uses the system-provided calloc() and free().
 * This allows different allocators (self-implemented or provided) to be
 * provided to the platform abstraction layer.
 *
 * Enabling MBEDTLS_PLATFORM_MEMORY without the
 * MBEDTLS_PLATFORM_{FREE,CALLOC}_MACROs will provide
 * "mbedtls_platform_set_calloc_free()" allowing you to set an alternative calloc() and
 * free() function pointer at runtime.
 *
 * Enabling MBEDTLS_PLATFORM_MEMORY and specifying
 * MBEDTLS_PLATFORM_{CALLOC,FREE}_MACROs will allow you to specify the
 * alternate function at compile time.
 *
 * Requires: MBEDTLS_PLATFORM_C
 *
 * Enable this layer to allow use of alternative memory allocators.
 */
#define MBEDTLS_PLATFORM_MEMORY

/**
 * \def MBEDTLS_MEMORY_BUFFER_ALLOC_C
 *
 * Enable the buffer allocator implementation that makes use of a (stack)
 * based buffer to 'allocate' dynamic memory. (replaces calloc() and free()
 * calls)
 *
 * Module:  library/memory_buffer_alloc.c
 *
 * Requires: MBEDTLS_PLATFORM_C
 *           MBEDTLS_PLATFORM_MEMORY (to use it within mbed TLS)
 *
 * Enable this module to enable the buffer memory allocator.
 */
#define MBEDTLS_MEMORY_BUFFER_ALLOC_C

/**
 * \def MBEDTLS_THREADING_ALT
 *
 * Provide your own alternate threading implementation.
 *
 * Requires: MBEDTLS_THREADING_C
 *
 * Uncomment this to allow your own alternate threading implementation.
 */
#define MBEDTLS_THREADING_ALT

/**
 * \def MBEDTLS_THREADING_C
 *
 * Enable the threading abstraction layer.
 * By default mbed TLS assumes it is used in a non-threaded environment or that
 * contexts are not shared between threads. If you do intend to use contexts
 * between threads, you will need to enable this layer to prevent race
 * conditions. See also our Knowledge Base article about threading:
 * https://mbed-tls.readthedocs.io/en/latest/kb/development/thread-safety-and-multi-threading
 *
 * Module:  library/threading.c
 *
 * This allows different threading implementations (self-implemented or
 * provided).
 *
 * You will have to enable either MBEDTLS_THREADING_ALT or
 * MBEDTLS_THREADING_PTHREAD.
 *
 * Enable this layer to allow use of mutexes within mbed TLS
 */
#define MBEDTLS_THREADING_C

#endif
/**
 * The cy-mbedtls-acceleration module supports only DP_SECP192R1,
 * SECP224R1, SECP256R1, SECP384R1 and SECP521R1 curves. If any
 * other curve is enabled, need to disable the MBEDTLS_ECP_ALT.
 */
#ifdef MBEDTLS_ECP_DP_SECP192K1_ENABLED
#undef MBEDTLS_ECP_ALT
#undef MBEDTLS_ECDH_GEN_PUBLIC_ALT
#undef MBEDTLS_ECDSA_SIGN_ALT
#undef MBEDTLS_ECDSA_VERIFY_ALT
#endif
#ifdef MBEDTLS_ECP_DP_SECP224K1_ENABLED
#undef MBEDTLS_ECP_ALT
#undef MBEDTLS_ECDH_GEN_PUBLIC_ALT
#undef MBEDTLS_ECDSA_SIGN_ALT
#undef MBEDTLS_ECDSA_VERIFY_ALT
#endif
#ifdef MBEDTLS_ECP_DP_SECP256K1_ENABLED
#undef MBEDTLS_ECP_ALT
#undef MBEDTLS_ECDH_GEN_PUBLIC_ALT
#undef MBEDTLS_ECDSA_SIGN_ALT
#undef MBEDTLS_ECDSA_VERIFY_ALT
#endif
#ifdef MBEDTLS_ECP_DP_BP256R1_ENABLED
#undef MBEDTLS_ECP_ALT
#undef MBEDTLS_ECDH_GEN_PUBLIC_ALT
#undef MBEDTLS_ECDSA_SIGN_ALT
#undef MBEDTLS_ECDSA_VERIFY_ALT
#endif
#ifdef MBEDTLS_ECP_DP_BP384R1_ENABLED
#undef MBEDTLS_ECP_ALT
#undef MBEDTLS_ECDH_GEN_PUBLIC_ALT
#undef MBEDTLS_ECDSA_SIGN_ALT
#undef MBEDTLS_ECDSA_VERIFY_ALT
#endif
#ifdef MBEDTLS_ECP_DP_BP512R1_ENABLED
#undef MBEDTLS_ECP_ALT
#undef MBEDTLS_ECDH_GEN_PUBLIC_ALT
#undef MBEDTLS_ECDSA_SIGN_ALT
#undef MBEDTLS_ECDSA_VERIFY_ALT
#endif
#ifdef MBEDTLS_ECP_DP_CURVE25519_ENABLED
#undef MBEDTLS_ECP_ALT
#undef MBEDTLS_ECDH_GEN_PUBLIC_ALT
#undef MBEDTLS_ECDSA_SIGN_ALT
#undef MBEDTLS_ECDSA_VERIFY_ALT
#endif

#endif /* DISABLE_MBEDTLS_ACCELERATION */

#endif /* MBEDTLS_USER_CONFIG_HEADER */

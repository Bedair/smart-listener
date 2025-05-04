# Model performance and validation report
**Source model:** conv1dlstm-medium-balanced-3.h5  
**Generated:** 2025-05-04 23:32:47

### Memory usage
| Model | Model memory | Scratch memory |
| :--- | :--- | :--- |
| float | 241,924 | 16,384 |

### Latency
| Layer | Cycles |
| :--- | :--- |
| CONV_2D | 340,120 |
| CONV_2D | 417,311 |
| CONV_2D | 729,305 |
| MAX_POOL_2D | 23,487 |
| CONV_2D | 699,663 |
| CONV_2D | 1,298,692 |
| MAX_POOL_2D | 22,237 |
| MEAN | 52,815 |
| FULLY_CONNECTED | 5,141 |
| SOFTMAX | 0 |
| **TOTAL** | **3,588,771** |

### Validation
**Validation data source:** None

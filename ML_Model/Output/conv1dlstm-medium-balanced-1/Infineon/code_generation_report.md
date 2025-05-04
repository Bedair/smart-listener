# Model performance and validation report
**Source model:** conv1dlstm-medium-balanced-1.h5  
**Generated:** 2025-05-04 13:36:10

### Memory usage
| Model | Model memory | Scratch memory |
| :--- | :--- | :--- |
| float | 73,960 | 16,384 |

### Latency
| Layer | Cycles |
| :--- | :--- |
| CONV_2D | 340,120 |
| CONV_2D | 203,623 |
| CONV_2D | 203,623 |
| MAX_POOL_2D | 11,682 |
| CONV_2D | 195,008 |
| CONV_2D | 344,765 |
| MAX_POOL_2D | 10,432 |
| MEAN | 27,216 |
| FULLY_CONNECTED | 2,780 |
| SOFTMAX | 0 |
| **TOTAL** | **1,339,249** |

### Validation
**Validation data source:** None

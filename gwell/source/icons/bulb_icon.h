#include "icons.h"

const QImage* Icons::bulbIcon()
{
  static const unsigned char bulb_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xe0, 0x77, 0x3d, 0xf8, 0x00, 0x00, 0x03,
    0x47, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xb5, 0x95, 0x4d, 0x68, 0x1d,
    0x55, 0x14, 0xc7, 0x7f, 0xf7, 0xde, 0x99, 0x97, 0xbc, 0x97, 0x87, 0x89,
    0x6d, 0xd2, 0x24, 0xad, 0x6d, 0x6d, 0x2d, 0xd8, 0xea, 0x42, 0x88, 0x01,
    0x6d, 0xdc, 0x45, 0x6c, 0x17, 0x82, 0x74, 0x27, 0x8a, 0x82, 0x96, 0x08,
    0x2e, 0x54, 0x94, 0xee, 0xdc, 0x08, 0xae, 0xba, 0x10, 0x3f, 0x8a, 0x3b,
    0x71, 0xa3, 0x8b, 0x26, 0x15, 0x8a, 0x2e, 0x44, 0x8a, 0x81, 0x12, 0x9b,
    0x06, 0xd1, 0x82, 0x18, 0x2b, 0xb6, 0x91, 0xda, 0x44, 0x68, 0xf3, 0x45,
    0xfb, 0xe2, 0x9b, 0xcc, 0xc7, 0x9b, 0x99, 0x7b, 0x8f, 0x8b, 0xa4, 0x35,
    0x98, 0x97, 0xbc, 0xd7, 0xa2, 0x07, 0xce, 0xe2, 0x0e, 0x73, 0xcf, 0xef,
    0xfc, 0x67, 0xce, 0x87, 0x9a, 0x98, 0x98, 0xe0, 0xff, 0x34, 0xdd, 0xe8,
    0x85, 0x33, 0x67, 0xce, 0xc9, 0x8d, 0x1b, 0x99, 0x94, 0xcb, 0xbb, 0xa5,
    0xbd, 0x7d, 0x9f, 0x44, 0x51, 0x49, 0xc6, 0xc6, 0x26, 0xe5, 0xd8, 0xb1,
    0xb7, 0xa5, 0x19, 0x80, 0xda, 0x4c, 0x41, 0xb1, 0xd8, 0x25, 0xdd, 0xdd,
    0x3d, 0x38, 0x27, 0xe4, 0xb9, 0x23, 0xcf, 0x1d, 0x59, 0xe6, 0x48, 0x33,
    0x8b, 0xcd, 0x1d, 0xc3, 0xc3, 0x9f, 0x72, 0xe4, 0xc8, 0xa0, 0xba, 0x2b,
    0x05, 0xbb, 0x76, 0xed, 0x97, 0x9d, 0x3b, 0x77, 0x50, 0x28, 0x18, 0x7c,
    0x5f, 0xe3, 0xfb, 0x06, 0xcf, 0xd3, 0x78, 0x9e, 0xc6, 0x18, 0x05, 0x06,
    0x9e, 0x7d, 0xee, 0x28, 0x63, 0xe7, 0x26, 0x37, 0x55, 0x52, 0x17, 0xd0,
    0xd1, 0xd1, 0x2b, 0xe5, 0x72, 0x89, 0x96, 0x16, 0xb3, 0x0a, 0xf8, 0x27,
    0xb8, 0xd6, 0x0a, 0xa3, 0x35, 0x5a, 0x29, 0x44, 0x09, 0x87, 0x0e, 0x3d,
    0xc3, 0x87, 0x1f, 0x7d, 0xb2, 0x21, 0x64, 0x1d, 0xe0, 0xfc, 0xf9, 0x1f,
    0xa5, 0xb7, 0xb7, 0x07, 0xdf, 0xd7, 0x6b, 0xb2, 0xd7, 0xf8, 0xbe, 0xc2,
    0xf3, 0x34, 0x85, 0xc2, 0xca, 0xd9, 0x18, 0x05, 0x08, 0x4e, 0x39, 0x5e,
    0x79, 0xf5, 0x2d, 0x06, 0x07, 0x9f, 0xac, 0x0b, 0xf1, 0xfe, 0xfd, 0xa0,
    0xbf, 0xff, 0x31, 0x94, 0x52, 0x28, 0xa5, 0x30, 0x46, 0xa1, 0xd4, 0x4a,
    0x1e, 0x4a, 0x81, 0xd6, 0xb7, 0x3e, 0x91, 0xc6, 0x21, 0x64, 0x92, 0x63,
    0x9d, 0xe3, 0xde, 0xce, 0x2d, 0xf4, 0x3d, 0xfa, 0x78, 0x5d, 0x05, 0xeb,
    0x00, 0x7b, 0xf6, 0x3c, 0x80, 0x73, 0x82, 0x73, 0x0e, 0x6b, 0x57, 0x65,
    0xea, 0x5b, 0x10, 0xc1, 0x98, 0x15, 0xb0, 0x13, 0x47, 0xcd, 0x69, 0x9c,
    0xb5, 0x60, 0x15, 0x3d, 0xbd, 0xf7, 0x35, 0x07, 0x30, 0xc6, 0x27, 0xcf,
    0xdd, 0x6a, 0x20, 0xc1, 0xf3, 0xf4, 0x6d, 0x88, 0xc8, 0x8a, 0xa2, 0x70,
    0x39, 0xc5, 0x18, 0x8d, 0xe7, 0x2b, 0x52, 0x2d, 0x88, 0x08, 0xbe, 0xef,
    0xd7, 0x05, 0xac, 0xfb, 0x07, 0xb3, 0xb3, 0x73, 0x64, 0x99, 0x5d, 0x75,
    0x47, 0x14, 0x06, 0x58, 0x2b, 0xb7, 0x3d, 0x49, 0x72, 0x72, 0x6b, 0xc9,
    0x5d, 0x8e, 0xf3, 0x2c, 0xd2, 0x0a, 0x78, 0x42, 0x35, 0xa8, 0x34, 0x07,
    0xb8, 0x70, 0xe1, 0x07, 0x92, 0x34, 0x23, 0xaa, 0x65, 0x44, 0x49, 0xc6,
    0xfc, 0x62, 0x85, 0x28, 0xce, 0x56, 0x3c, 0x4a, 0x89, 0x6b, 0x39, 0xc1,
    0x72, 0x95, 0xd8, 0x26, 0x64, 0x5e, 0x8e, 0xf8, 0x0e, 0x94, 0xe2, 0xd7,
    0x5f, 0x7e, 0xae, 0x0b, 0xa8, 0xdb, 0x68, 0x1d, 0x9d, 0xfb, 0xc4, 0x15,
    0x2c, 0x9e, 0xd6, 0x14, 0x34, 0xd8, 0xac, 0x86, 0xf1, 0xdb, 0x70, 0x4e,
    0x50, 0xc0, 0xa5, 0xa9, 0x8b, 0x6c, 0xdf, 0x7f, 0x3f, 0xb6, 0xcd, 0x21,
    0xb1, 0x66, 0xec, 0xf4, 0x28, 0x03, 0x7d, 0x0f, 0xd5, 0x6d, 0xb8, 0xba,
    0x7d, 0x30, 0x72, 0xf2, 0x73, 0xf2, 0x44, 0x58, 0xb6, 0x35, 0x62, 0x1c,
    0xbf, 0x5d, 0xfd, 0x9d, 0x9b, 0xf1, 0x32, 0x4b, 0x51, 0x40, 0xe5, 0xaf,
    0x3f, 0xe9, 0xda, 0xdd, 0x45, 0xde, 0xe2, 0x10, 0x07, 0xf1, 0x42, 0xc2,
    0x07, 0xc7, 0xdf, 0xad, 0x9b, 0xfd, 0x86, 0x80, 0xc3, 0x4f, 0x1d, 0x54,
    0xa3, 0x5f, 0x7f, 0x83, 0x0a, 0x0c, 0x61, 0x35, 0xa1, 0xe8, 0x3b, 0x5c,
    0x56, 0x45, 0x5c, 0x95, 0xc5, 0x4a, 0x80, 0x2a, 0x14, 0x90, 0x58, 0x88,
    0xaf, 0xa5, 0xbc, 0x39, 0xf4, 0x12, 0x5f, 0x9c, 0x1a, 0xde, 0x70, 0x5c,
    0x6c, 0x38, 0x2a, 0x06, 0x0e, 0x1e, 0x50, 0xef, 0x1d, 0x7f, 0x87, 0x78,
    0xf6, 0x0a, 0x2e, 0x4c, 0x09, 0xe7, 0xaf, 0x43, 0x30, 0x4f, 0x57, 0x6b,
    0x82, 0xcc, 0x4d, 0xf3, 0xd3, 0xe8, 0xb7, 0x3c, 0xff, 0xf4, 0x61, 0x3e,
    0x3e, 0xf1, 0xfe, 0xa6, 0xb3, 0x68, 0x5d, 0x99, 0xae, 0xb5, 0xd7, 0x5f,
    0x3b, 0xaa, 0xf6, 0x76, 0xdf, 0x94, 0x4c, 0x6d, 0x27, 0xb3, 0x06, 0x97,
    0x87, 0x28, 0x5b, 0x25, 0xa8, 0x5c, 0xe6, 0xf4, 0x67, 0x27, 0x38, 0x35,
    0x72, 0x72, 0xd3, 0xe0, 0x0d, 0x01, 0x00, 0xa5, 0x52, 0x99, 0xa8, 0x7a,
    0x11, 0x1b, 0x47, 0x44, 0x4b, 0xd3, 0x84, 0x51, 0x42, 0x92, 0xb5, 0x52,
    0x2a, 0xd6, 0xaf, 0xfb, 0x3b, 0x06, 0xd8, 0xda, 0x02, 0xed, 0xdb, 0x1e,
    0xe1, 0x1e, 0x1b, 0x53, 0x6a, 0x2b, 0x11, 0x86, 0x11, 0x33, 0x33, 0xd3,
    0xa4, 0x79, 0xc3, 0xab, 0xcd, 0x01, 0x8c, 0xdf, 0x41, 0xb8, 0x1c, 0x51,
    0x4b, 0x53, 0x82, 0xa5, 0x8c, 0x28, 0x8c, 0x29, 0x16, 0xb7, 0xa0, 0x49,
    0xff, 0x1b, 0x40, 0x2e, 0x05, 0x6a, 0xf1, 0x3c, 0xc1, 0xd2, 0x75, 0x2a,
    0x0b, 0x53, 0x04, 0x41, 0x00, 0xde, 0x56, 0x6a, 0x69, 0xde, 0x14, 0xa0,
    0xe1, 0xca, 0xfc, 0xea, 0xcb, 0x11, 0xfc, 0x96, 0x32, 0x1d, 0x9d, 0x7b,
    0xd9, 0xda, 0x73, 0x80, 0x6d, 0x3b, 0x1e, 0xe6, 0xd2, 0xe5, 0x2b, 0x8c,
    0x7d, 0x7f, 0xb5, 0x29, 0x40, 0x43, 0x05, 0x0f, 0xf6, 0xbd, 0xa8, 0x5e,
    0x78, 0xf9, 0x0d, 0x79, 0x62, 0xa0, 0x9f, 0xc5, 0x85, 0x6b, 0x8c, 0x4f,
    0x4c, 0xf2, 0xc7, 0xcc, 0x1c, 0x67, 0xcf, 0x7e, 0xd7, 0xb0, 0x82, 0xa0,
    0xc1, 0x4e, 0x5e, 0x6b, 0x43, 0x43, 0x43, 0xe2, 0x9c, 0x63, 0x6a, 0x6a,
    0x8a, 0xf1, 0xf1, 0xf1, 0xa6, 0x82, 0xdf, 0x11, 0xe0, 0x6e, 0xed, 0x6f,
    0x78, 0x7f, 0x8a, 0xd7, 0x65, 0x89, 0xd2, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82};
        
    static QImage img;
    img.loadFromData( bulb_data, sizeof( bulb_data ) );
    
    return ( &img );
};

#ifndef TESSY_DEFINES_H
#define TESSY_DEFINES_H

#define TRUE        (1U)
#define FALSE       (0U)

typedef unsigned char  Ifx_UReg_8Bit;
typedef unsigned short Ifx_UReg_16Bit;
typedef unsigned int   Ifx_UReg_32Bit;
typedef signed char    Ifx_SReg_8Bit;
typedef signed short   Ifx_SReg_16Bit;
typedef signed int     Ifx_SReg_32Bit;

/******************************************************************************/


/** \addtogroup IfxSfr_P_Registers_Bitfields
 * \{  */
/** \brief Port n Access Enable Register 0 */
typedef struct _Ifx_P_ACCEN0_Bits
{
    Ifx_UReg_32Bit EN0:1;             /**< \brief [0:0] Access Enable for Master TAG ID 0 (rw) */
    Ifx_UReg_32Bit EN1:1;             /**< \brief [1:1] Access Enable for Master TAG ID 1 (rw) */
    Ifx_UReg_32Bit EN2:1;             /**< \brief [2:2] Access Enable for Master TAG ID 2 (rw) */
    Ifx_UReg_32Bit EN3:1;             /**< \brief [3:3] Access Enable for Master TAG ID 3 (rw) */
    Ifx_UReg_32Bit EN4:1;             /**< \brief [4:4] Access Enable for Master TAG ID 4 (rw) */
    Ifx_UReg_32Bit EN5:1;             /**< \brief [5:5] Access Enable for Master TAG ID 5 (rw) */
    Ifx_UReg_32Bit EN6:1;             /**< \brief [6:6] Access Enable for Master TAG ID 6 (rw) */
    Ifx_UReg_32Bit EN7:1;             /**< \brief [7:7] Access Enable for Master TAG ID 7 (rw) */
    Ifx_UReg_32Bit EN8:1;             /**< \brief [8:8] Access Enable for Master TAG ID 8 (rw) */
    Ifx_UReg_32Bit EN9:1;             /**< \brief [9:9] Access Enable for Master TAG ID 9 (rw) */
    Ifx_UReg_32Bit EN10:1;            /**< \brief [10:10] Access Enable for Master TAG ID 10 (rw) */
    Ifx_UReg_32Bit EN11:1;            /**< \brief [11:11] Access Enable for Master TAG ID 11 (rw) */
    Ifx_UReg_32Bit EN12:1;            /**< \brief [12:12] Access Enable for Master TAG ID 12 (rw) */
    Ifx_UReg_32Bit EN13:1;            /**< \brief [13:13] Access Enable for Master TAG ID 13 (rw) */
    Ifx_UReg_32Bit EN14:1;            /**< \brief [14:14] Access Enable for Master TAG ID 14 (rw) */
    Ifx_UReg_32Bit EN15:1;            /**< \brief [15:15] Access Enable for Master TAG ID 15 (rw) */
    Ifx_UReg_32Bit EN16:1;            /**< \brief [16:16] Access Enable for Master TAG ID 16 (rw) */
    Ifx_UReg_32Bit EN17:1;            /**< \brief [17:17] Access Enable for Master TAG ID 17 (rw) */
    Ifx_UReg_32Bit EN18:1;            /**< \brief [18:18] Access Enable for Master TAG ID 18 (rw) */
    Ifx_UReg_32Bit EN19:1;            /**< \brief [19:19] Access Enable for Master TAG ID 19 (rw) */
    Ifx_UReg_32Bit EN20:1;            /**< \brief [20:20] Access Enable for Master TAG ID 20 (rw) */
    Ifx_UReg_32Bit EN21:1;            /**< \brief [21:21] Access Enable for Master TAG ID 21 (rw) */
    Ifx_UReg_32Bit EN22:1;            /**< \brief [22:22] Access Enable for Master TAG ID 22 (rw) */
    Ifx_UReg_32Bit EN23:1;            /**< \brief [23:23] Access Enable for Master TAG ID 23 (rw) */
    Ifx_UReg_32Bit EN24:1;            /**< \brief [24:24] Access Enable for Master TAG ID 24 (rw) */
    Ifx_UReg_32Bit EN25:1;            /**< \brief [25:25] Access Enable for Master TAG ID 25 (rw) */
    Ifx_UReg_32Bit EN26:1;            /**< \brief [26:26] Access Enable for Master TAG ID 26 (rw) */
    Ifx_UReg_32Bit EN27:1;            /**< \brief [27:27] Access Enable for Master TAG ID 27 (rw) */
    Ifx_UReg_32Bit EN28:1;            /**< \brief [28:28] Access Enable for Master TAG ID 28 (rw) */
    Ifx_UReg_32Bit EN29:1;            /**< \brief [29:29] Access Enable for Master TAG ID 29 (rw) */
    Ifx_UReg_32Bit EN30:1;            /**< \brief [30:30] Access Enable for Master TAG ID 30 (rw) */
    Ifx_UReg_32Bit EN31:1;            /**< \brief [31:31] Access Enable for Master TAG ID 31 (rw) */
} Ifx_P_ACCEN0_Bits;

/** \brief Port n Access Enable Register 1 */
typedef struct _Ifx_P_ACCEN1_Bits
{
    Ifx_UReg_32Bit reserved_0:32;     /**< \brief [31:0] \internal Reserved */
} Ifx_P_ACCEN1_Bits;

/** \brief Port n Emergency Stop Register */
typedef struct _Ifx_P_ESR_Bits
{
    Ifx_UReg_32Bit EN0:1;             /**< \brief [0:0] Emergency Stop Enable for Pin 0 (rw) */
    Ifx_UReg_32Bit EN1:1;             /**< \brief [1:1] Emergency Stop Enable for Pin 1 (rw) */
    Ifx_UReg_32Bit EN2:1;             /**< \brief [2:2] Emergency Stop Enable for Pin 2 (rw) */
    Ifx_UReg_32Bit EN3:1;             /**< \brief [3:3] Emergency Stop Enable for Pin 3 (rw) */
    Ifx_UReg_32Bit EN4:1;             /**< \brief [4:4] Emergency Stop Enable for Pin 4 (rw) */
    Ifx_UReg_32Bit EN5:1;             /**< \brief [5:5] Emergency Stop Enable for Pin 5 (rw) */
    Ifx_UReg_32Bit EN6:1;             /**< \brief [6:6] Emergency Stop Enable for Pin 6 (rw) */
    Ifx_UReg_32Bit EN7:1;             /**< \brief [7:7] Emergency Stop Enable for Pin 7 (rw) */
    Ifx_UReg_32Bit EN8:1;             /**< \brief [8:8] Emergency Stop Enable for Pin 8 (rw) */
    Ifx_UReg_32Bit EN9:1;             /**< \brief [9:9] Emergency Stop Enable for Pin 9 (rw) */
    Ifx_UReg_32Bit EN10:1;            /**< \brief [10:10] Emergency Stop Enable for Pin 10 (rw) */
    Ifx_UReg_32Bit EN11:1;            /**< \brief [11:11] Emergency Stop Enable for Pin 11 (rw) */
    Ifx_UReg_32Bit EN12:1;            /**< \brief [12:12] Emergency Stop Enable for Pin 12 (rw) */
    Ifx_UReg_32Bit EN13:1;            /**< \brief [13:13] Emergency Stop Enable for Pin 13 (rw) */
    Ifx_UReg_32Bit EN14:1;            /**< \brief [14:14] Emergency Stop Enable for Pin 14 (rw) */
    Ifx_UReg_32Bit EN15:1;            /**< \brief [15:15] Emergency Stop Enable for Pin 15 (rw) */
    Ifx_UReg_32Bit reserved_16:16;    /**< \brief [31:16] \internal Reserved */
} Ifx_P_ESR_Bits;

/** \brief Port n Identification Register */
typedef struct _Ifx_P_ID_Bits
{
    Ifx_UReg_32Bit MODREV:8;          /**< \brief [7:0] Module Revision Number (r) */
    Ifx_UReg_32Bit MODTYPE:8;         /**< \brief [15:8] Module Type (r) */
    Ifx_UReg_32Bit MODNUMBER:16;      /**< \brief [31:16] Module Number (r) */
} Ifx_P_ID_Bits;

/** \brief Port n Input Register */
typedef struct _Ifx_P_IN_Bits
{
    Ifx_UReg_32Bit P0:1;              /**< \brief [0:0] Input Bit 0 (rh) */
    Ifx_UReg_32Bit P1:1;              /**< \brief [1:1] Input Bit 1 (rh) */
    Ifx_UReg_32Bit P2:1;              /**< \brief [2:2] Input Bit 2 (rh) */
    Ifx_UReg_32Bit P3:1;              /**< \brief [3:3] Input Bit 3 (rh) */
    Ifx_UReg_32Bit P4:1;              /**< \brief [4:4] Input Bit 4 (rh) */
    Ifx_UReg_32Bit P5:1;              /**< \brief [5:5] Input Bit 5 (rh) */
    Ifx_UReg_32Bit P6:1;              /**< \brief [6:6] Input Bit 6 (rh) */
    Ifx_UReg_32Bit P7:1;              /**< \brief [7:7] Input Bit 7 (rh) */
    Ifx_UReg_32Bit P8:1;              /**< \brief [8:8] Input Bit 8 (rh) */
    Ifx_UReg_32Bit P9:1;              /**< \brief [9:9] Input Bit 9 (rh) */
    Ifx_UReg_32Bit P10:1;             /**< \brief [10:10] Input Bit 10 (rh) */
    Ifx_UReg_32Bit P11:1;             /**< \brief [11:11] Input Bit 11 (rh) */
    Ifx_UReg_32Bit P12:1;             /**< \brief [12:12] Input Bit 12 (rh) */
    Ifx_UReg_32Bit P13:1;             /**< \brief [13:13] Input Bit 13 (rh) */
    Ifx_UReg_32Bit P14:1;             /**< \brief [14:14] Input Bit 14 (rh) */
    Ifx_UReg_32Bit P15:1;             /**< \brief [15:15] Input Bit 15 (rh) */
    Ifx_UReg_32Bit reserved_16:16;    /**< \brief [31:16] \internal Reserved */
} Ifx_P_IN_Bits;

/** \brief Port n Input/Output Control Register 0 */
typedef struct _Ifx_P_IOCR0_Bits
{
    Ifx_UReg_32Bit reserved_0:3;      /**< \brief [2:0] \internal Reserved */
    Ifx_UReg_32Bit PC0:5;             /**< \brief [7:3] Port Control for Pin 0 (rw) */
    Ifx_UReg_32Bit reserved_8:3;      /**< \brief [10:8] \internal Reserved */
    Ifx_UReg_32Bit PC1:5;             /**< \brief [15:11] Port Control for Pin 1 (rw) */
    Ifx_UReg_32Bit reserved_16:3;     /**< \brief [18:16] \internal Reserved */
    Ifx_UReg_32Bit PC2:5;             /**< \brief [23:19] Port Control for Pin 2 (rw) */
    Ifx_UReg_32Bit reserved_24:3;     /**< \brief [26:24] \internal Reserved */
    Ifx_UReg_32Bit PC3:5;             /**< \brief [31:27] Port Control for Pin 3 (rw) */
} Ifx_P_IOCR0_Bits;

/** \brief Port n Input/Output Control Register 12 */
typedef struct _Ifx_P_IOCR12_Bits
{
    Ifx_UReg_32Bit reserved_0:3;      /**< \brief [2:0] \internal Reserved */
    Ifx_UReg_32Bit PC12:5;            /**< \brief [7:3] Port Control for Port n Pin 12 (rw) */
    Ifx_UReg_32Bit reserved_8:3;      /**< \brief [10:8] \internal Reserved */
    Ifx_UReg_32Bit PC13:5;            /**< \brief [15:11] Port Control for Port n Pin 13 (rw) */
    Ifx_UReg_32Bit reserved_16:3;     /**< \brief [18:16] \internal Reserved */
    Ifx_UReg_32Bit PC14:5;            /**< \brief [23:19] Port Control for Port n Pin 14 (rw) */
    Ifx_UReg_32Bit reserved_24:3;     /**< \brief [26:24] \internal Reserved */
    Ifx_UReg_32Bit PC15:5;            /**< \brief [31:27] Port Control for Port n Pin 15 (rw) */
} Ifx_P_IOCR12_Bits;

/** \brief Port n Input/Output Control Register 4 */
typedef struct _Ifx_P_IOCR4_Bits
{
    Ifx_UReg_32Bit reserved_0:3;      /**< \brief [2:0] \internal Reserved */
    Ifx_UReg_32Bit PC4:5;             /**< \brief [7:3] Port Control for Port n Pin 4 (rw) */
    Ifx_UReg_32Bit reserved_8:3;      /**< \brief [10:8] \internal Reserved */
    Ifx_UReg_32Bit PC5:5;             /**< \brief [15:11] Port Control for Port n Pin 5 (rw) */
    Ifx_UReg_32Bit reserved_16:3;     /**< \brief [18:16] \internal Reserved */
    Ifx_UReg_32Bit PC6:5;             /**< \brief [23:19] Port Control for Port n Pin 6 (rw) */
    Ifx_UReg_32Bit reserved_24:3;     /**< \brief [26:24] \internal Reserved */
    Ifx_UReg_32Bit PC7:5;             /**< \brief [31:27] Port Control for Port n Pin 7 (rw) */
} Ifx_P_IOCR4_Bits;

/** \brief Port n Input/Output Control Register 8 */
typedef struct _Ifx_P_IOCR8_Bits
{
    Ifx_UReg_32Bit reserved_0:3;      /**< \brief [2:0] \internal Reserved */
    Ifx_UReg_32Bit PC8:5;             /**< \brief [7:3] Port Control for Port n Pin 8 (rw) */
    Ifx_UReg_32Bit reserved_8:3;      /**< \brief [10:8] \internal Reserved */
    Ifx_UReg_32Bit PC9:5;             /**< \brief [15:11] Port Control for Port n Pin 9 (rw) */
    Ifx_UReg_32Bit reserved_16:3;     /**< \brief [18:16] \internal Reserved */
    Ifx_UReg_32Bit PC10:5;            /**< \brief [23:19] Port Control for Port n Pin 10 (rw) */
    Ifx_UReg_32Bit reserved_24:3;     /**< \brief [26:24] \internal Reserved */
    Ifx_UReg_32Bit PC11:5;            /**< \brief [31:27] Port Control for Port n Pin 11 (rw) */
} Ifx_P_IOCR8_Bits;

/** \brief Port n LVDS Pad Control Register ${x} */
typedef struct _Ifx_P_LPCR_Bits
{
    Ifx_UReg_32Bit REN_CTRL:1;        /**< \brief [0:0] LVDS RX_EN controller (rw) */
    Ifx_UReg_32Bit RX_EN:1;           /**< \brief [1:1] Enable Receive LVDS (rw) */
    Ifx_UReg_32Bit TERM:1;            /**< \brief [2:2] Select Receiver Termination Mode (rw) */
    Ifx_UReg_32Bit LRXTERM:3;         /**< \brief [5:3] LVDS RX Poly-resistor configuration value (rw) */
    Ifx_UReg_32Bit LVDSM:1;           /**< \brief [6:6] LVDS-M Mode (rw) */
    Ifx_UReg_32Bit PS:1;              /**< \brief [7:7] Pad Supply Selection (rw) */
    Ifx_UReg_32Bit TEN_CTRL:1;        /**< \brief [8:8] LVDS TX_EN controller (rw) */
    Ifx_UReg_32Bit TX_EN:1;           /**< \brief [9:9] Enable Transmit LVDS (rw) */
    Ifx_UReg_32Bit VDIFFADJ:2;        /**< \brief [11:10] LVDS Output Amplitude Tuning (rw) */
    Ifx_UReg_32Bit VOSDYN:1;          /**< \brief [12:12] Tune Bit of VOS Control Loop Static/Dynamic (rw) */
    Ifx_UReg_32Bit VOSEXT:1;          /**< \brief [13:13] Tune Bit of VOS Control Loop Internal/External (rw) */
    Ifx_UReg_32Bit TX_PD:1;           /**< \brief [14:14] LVDS Power Down (rw) */
    Ifx_UReg_32Bit TX_PWDPD:1;        /**< \brief [15:15] Enable TX Power down pull down. (rw) */
    Ifx_UReg_32Bit reserved_16:16;    /**< \brief [31:16] \internal Reserved */
} Ifx_P_LPCR_Bits;

/** \brief Port n Output Modification Clear Register */
typedef struct _Ifx_P_OMCR_Bits
{
    Ifx_UReg_32Bit reserved_0:16;     /**< \brief [15:0] \internal Reserved */
    Ifx_UReg_32Bit PCL0:1;            /**< \brief [16:16] Clear Bit 0 (w) */
    Ifx_UReg_32Bit PCL1:1;            /**< \brief [17:17] Clear Bit 1 (w) */
    Ifx_UReg_32Bit PCL2:1;            /**< \brief [18:18] Clear Bit 2 (w) */
    Ifx_UReg_32Bit PCL3:1;            /**< \brief [19:19] Clear Bit 3 (w) */
    Ifx_UReg_32Bit PCL4:1;            /**< \brief [20:20] Clear Bit 4 (w) */
    Ifx_UReg_32Bit PCL5:1;            /**< \brief [21:21] Clear Bit 5 (w) */
    Ifx_UReg_32Bit PCL6:1;            /**< \brief [22:22] Clear Bit 6 (w) */
    Ifx_UReg_32Bit PCL7:1;            /**< \brief [23:23] Clear Bit 7 (w) */
    Ifx_UReg_32Bit PCL8:1;            /**< \brief [24:24] Clear Bit 8 (w) */
    Ifx_UReg_32Bit PCL9:1;            /**< \brief [25:25] Clear Bit 9 (w) */
    Ifx_UReg_32Bit PCL10:1;           /**< \brief [26:26] Clear Bit 10 (w) */
    Ifx_UReg_32Bit PCL11:1;           /**< \brief [27:27] Clear Bit 11 (w) */
    Ifx_UReg_32Bit PCL12:1;           /**< \brief [28:28] Clear Bit 12 (w) */
    Ifx_UReg_32Bit PCL13:1;           /**< \brief [29:29] Clear Bit 13 (w) */
    Ifx_UReg_32Bit PCL14:1;           /**< \brief [30:30] Clear Bit 14 (w) */
    Ifx_UReg_32Bit PCL15:1;           /**< \brief [31:31] Clear Bit 15 (w) */
} Ifx_P_OMCR_Bits;

/** \brief Port n Output Modification Clear Register 0 */
typedef struct _Ifx_P_OMCR0_Bits
{
    Ifx_UReg_32Bit reserved_0:16;     /**< \brief [15:0] \internal Reserved */
    Ifx_UReg_32Bit PCL0:1;            /**< \brief [16:16] Clear Bit 0 (w) */
    Ifx_UReg_32Bit PCL1:1;            /**< \brief [17:17] Clear Bit 1 (w) */
    Ifx_UReg_32Bit PCL2:1;            /**< \brief [18:18] Clear Bit 2 (w) */
    Ifx_UReg_32Bit PCL3:1;            /**< \brief [19:19] Clear Bit 3 (w) */
    Ifx_UReg_32Bit reserved_20:12;    /**< \brief [31:20] \internal Reserved */
} Ifx_P_OMCR0_Bits;

/** \brief Port n Output Modification Clear Register 12 */
typedef struct _Ifx_P_OMCR12_Bits
{
    Ifx_UReg_32Bit reserved_0:28;     /**< \brief [27:0] \internal Reserved */
    Ifx_UReg_32Bit PCL12:1;           /**< \brief [28:28] Clear Bit 12 (w) */
    Ifx_UReg_32Bit PCL13:1;           /**< \brief [29:29] Clear Bit 13 (w) */
    Ifx_UReg_32Bit PCL14:1;           /**< \brief [30:30] Clear Bit 14 (w) */
    Ifx_UReg_32Bit PCL15:1;           /**< \brief [31:31] Clear Bit 15 (w) */
} Ifx_P_OMCR12_Bits;

/** \brief Port n Output Modification Clear Register 4 */
typedef struct _Ifx_P_OMCR4_Bits
{
    Ifx_UReg_32Bit reserved_0:20;     /**< \brief [19:0] \internal Reserved */
    Ifx_UReg_32Bit PCL4:1;            /**< \brief [20:20] Clear Bit 4 (w) */
    Ifx_UReg_32Bit PCL5:1;            /**< \brief [21:21] Clear Bit 5 (w) */
    Ifx_UReg_32Bit PCL6:1;            /**< \brief [22:22] Clear Bit 6 (w) */
    Ifx_UReg_32Bit PCL7:1;            /**< \brief [23:23] Clear Bit 7 (w) */
    Ifx_UReg_32Bit reserved_24:8;     /**< \brief [31:24] \internal Reserved */
} Ifx_P_OMCR4_Bits;

/** \brief Port n Output Modification Clear Register 8 */
typedef struct _Ifx_P_OMCR8_Bits
{
    Ifx_UReg_32Bit reserved_0:24;     /**< \brief [23:0] \internal Reserved */
    Ifx_UReg_32Bit PCL8:1;            /**< \brief [24:24] Clear Bit 8 (w) */
    Ifx_UReg_32Bit PCL9:1;            /**< \brief [25:25] Clear Bit 9 (w) */
    Ifx_UReg_32Bit PCL10:1;           /**< \brief [26:26] Clear Bit 10 (w) */
    Ifx_UReg_32Bit PCL11:1;           /**< \brief [27:27] Clear Bit 11 (w) */
    Ifx_UReg_32Bit reserved_28:4;     /**< \brief [31:28] \internal Reserved */
} Ifx_P_OMCR8_Bits;

/** \brief Port n Output Modification Register */
typedef struct _Ifx_P_OMR_Bits
{
    Ifx_UReg_32Bit PS0:1;             /**< \brief [0:0] Set Bit 0 (w) */
    Ifx_UReg_32Bit PS1:1;             /**< \brief [1:1] Set Bit 1 (w) */
    Ifx_UReg_32Bit PS2:1;             /**< \brief [2:2] Set Bit 2 (w) */
    Ifx_UReg_32Bit PS3:1;             /**< \brief [3:3] Set Bit 3 (w) */
    Ifx_UReg_32Bit PS4:1;             /**< \brief [4:4] Set Bit 4 (w) */
    Ifx_UReg_32Bit PS5:1;             /**< \brief [5:5] Set Bit 5 (w) */
    Ifx_UReg_32Bit PS6:1;             /**< \brief [6:6] Set Bit 6 (w) */
    Ifx_UReg_32Bit PS7:1;             /**< \brief [7:7] Set Bit 7 (w) */
    Ifx_UReg_32Bit PS8:1;             /**< \brief [8:8] Set Bit 8 (w) */
    Ifx_UReg_32Bit PS9:1;             /**< \brief [9:9] Set Bit 9 (w) */
    Ifx_UReg_32Bit PS10:1;            /**< \brief [10:10] Set Bit 10 (w) */
    Ifx_UReg_32Bit PS11:1;            /**< \brief [11:11] Set Bit 11 (w) */
    Ifx_UReg_32Bit PS12:1;            /**< \brief [12:12] Set Bit 12 (w) */
    Ifx_UReg_32Bit PS13:1;            /**< \brief [13:13] Set Bit 13 (w) */
    Ifx_UReg_32Bit PS14:1;            /**< \brief [14:14] Set Bit 14 (w) */
    Ifx_UReg_32Bit PS15:1;            /**< \brief [15:15] Set Bit 15 (w) */
    Ifx_UReg_32Bit PCL0:1;            /**< \brief [16:16] Clear Bit 0 (w) */
    Ifx_UReg_32Bit PCL1:1;            /**< \brief [17:17] Clear Bit 1 (w) */
    Ifx_UReg_32Bit PCL2:1;            /**< \brief [18:18] Clear Bit 2 (w) */
    Ifx_UReg_32Bit PCL3:1;            /**< \brief [19:19] Clear Bit 3 (w) */
    Ifx_UReg_32Bit PCL4:1;            /**< \brief [20:20] Clear Bit 4 (w) */
    Ifx_UReg_32Bit PCL5:1;            /**< \brief [21:21] Clear Bit 5 (w) */
    Ifx_UReg_32Bit PCL6:1;            /**< \brief [22:22] Clear Bit 6 (w) */
    Ifx_UReg_32Bit PCL7:1;            /**< \brief [23:23] Clear Bit 7 (w) */
    Ifx_UReg_32Bit PCL8:1;            /**< \brief [24:24] Clear Bit 8 (w) */
    Ifx_UReg_32Bit PCL9:1;            /**< \brief [25:25] Clear Bit 9 (w) */
    Ifx_UReg_32Bit PCL10:1;           /**< \brief [26:26] Clear Bit 10 (w) */
    Ifx_UReg_32Bit PCL11:1;           /**< \brief [27:27] Clear Bit 11 (w) */
    Ifx_UReg_32Bit PCL12:1;           /**< \brief [28:28] Clear Bit 12 (w) */
    Ifx_UReg_32Bit PCL13:1;           /**< \brief [29:29] Clear Bit 13 (w) */
    Ifx_UReg_32Bit PCL14:1;           /**< \brief [30:30] Clear Bit 14 (w) */
    Ifx_UReg_32Bit PCL15:1;           /**< \brief [31:31] Clear Bit 15 (w) */
} Ifx_P_OMR_Bits;

/** \brief Port n Output Modification Set Register */
typedef struct _Ifx_P_OMSR_Bits
{
    Ifx_UReg_32Bit PS0:1;             /**< \brief [0:0] Set Bit 0 (w) */
    Ifx_UReg_32Bit PS1:1;             /**< \brief [1:1] Set Bit 1 (w) */
    Ifx_UReg_32Bit PS2:1;             /**< \brief [2:2] Set Bit 2 (w) */
    Ifx_UReg_32Bit PS3:1;             /**< \brief [3:3] Set Bit 3 (w) */
    Ifx_UReg_32Bit PS4:1;             /**< \brief [4:4] Set Bit 4 (w) */
    Ifx_UReg_32Bit PS5:1;             /**< \brief [5:5] Set Bit 5 (w) */
    Ifx_UReg_32Bit PS6:1;             /**< \brief [6:6] Set Bit 6 (w) */
    Ifx_UReg_32Bit PS7:1;             /**< \brief [7:7] Set Bit 7 (w) */
    Ifx_UReg_32Bit PS8:1;             /**< \brief [8:8] Set Bit 8 (w) */
    Ifx_UReg_32Bit PS9:1;             /**< \brief [9:9] Set Bit 9 (w) */
    Ifx_UReg_32Bit PS10:1;            /**< \brief [10:10] Set Bit 10 (w) */
    Ifx_UReg_32Bit PS11:1;            /**< \brief [11:11] Set Bit 11 (w) */
    Ifx_UReg_32Bit PS12:1;            /**< \brief [12:12] Set Bit 12 (w) */
    Ifx_UReg_32Bit PS13:1;            /**< \brief [13:13] Set Bit 13 (w) */
    Ifx_UReg_32Bit PS14:1;            /**< \brief [14:14] Set Bit 14 (w) */
    Ifx_UReg_32Bit PS15:1;            /**< \brief [15:15] Set Bit 15 (w) */
    Ifx_UReg_32Bit reserved_16:16;    /**< \brief [31:16] \internal Reserved */
} Ifx_P_OMSR_Bits;

/** \brief Port n Output Modification Set Register 0 */
typedef struct _Ifx_P_OMSR0_Bits
{
    Ifx_UReg_32Bit PS0:1;             /**< \brief [0:0] Set Bit 0 (w) */
    Ifx_UReg_32Bit PS1:1;             /**< \brief [1:1] Set Bit 1 (w) */
    Ifx_UReg_32Bit PS2:1;             /**< \brief [2:2] Set Bit 2 (w) */
    Ifx_UReg_32Bit PS3:1;             /**< \brief [3:3] Set Bit 3 (w) */
    Ifx_UReg_32Bit reserved_4:28;     /**< \brief [31:4] \internal Reserved */
} Ifx_P_OMSR0_Bits;

/** \brief Port n Output Modification Set Register 12 */
typedef struct _Ifx_P_OMSR12_Bits
{
    Ifx_UReg_32Bit reserved_0:12;     /**< \brief [11:0] \internal Reserved */
    Ifx_UReg_32Bit PS12:1;            /**< \brief [12:12] Set Bit 12 (w) */
    Ifx_UReg_32Bit PS13:1;            /**< \brief [13:13] Set Bit 13 (w) */
    Ifx_UReg_32Bit PS14:1;            /**< \brief [14:14] Set Bit 14 (w) */
    Ifx_UReg_32Bit PS15:1;            /**< \brief [15:15] Set Bit 15 (w) */
    Ifx_UReg_32Bit reserved_16:16;    /**< \brief [31:16] \internal Reserved */
} Ifx_P_OMSR12_Bits;

/** \brief Port n Output Modification Set Register 4 */
typedef struct _Ifx_P_OMSR4_Bits
{
    Ifx_UReg_32Bit reserved_0:4;      /**< \brief [3:0] \internal Reserved */
    Ifx_UReg_32Bit PS4:1;             /**< \brief [4:4] Set Bit 4 (w) */
    Ifx_UReg_32Bit PS5:1;             /**< \brief [5:5] Set Bit 5 (w) */
    Ifx_UReg_32Bit PS6:1;             /**< \brief [6:6] Set Bit 6 (w) */
    Ifx_UReg_32Bit PS7:1;             /**< \brief [7:7] Set Bit 7 (w) */
    Ifx_UReg_32Bit reserved_8:24;     /**< \brief [31:8] \internal Reserved */
} Ifx_P_OMSR4_Bits;

/** \brief Port n Output Modification Set Register 8 */
typedef struct _Ifx_P_OMSR8_Bits
{
    Ifx_UReg_32Bit reserved_0:8;      /**< \brief [7:0] \internal Reserved */
    Ifx_UReg_32Bit PS8:1;             /**< \brief [8:8] Set Bit 8 (w) */
    Ifx_UReg_32Bit PS9:1;             /**< \brief [9:9] Set Bit 9 (w) */
    Ifx_UReg_32Bit PS10:1;            /**< \brief [10:10] Set Bit 10 (w) */
    Ifx_UReg_32Bit PS11:1;            /**< \brief [11:11] Set Bit 11 (w) */
    Ifx_UReg_32Bit reserved_12:20;    /**< \brief [31:12] \internal Reserved */
} Ifx_P_OMSR8_Bits;

/** \brief Port n Output Register */
typedef struct _Ifx_P_OUT_Bits
{
    Ifx_UReg_32Bit P0:1;              /**< \brief [0:0] Output Bit 0 (rwh) */
    Ifx_UReg_32Bit P1:1;              /**< \brief [1:1] Output Bit 1 (rwh) */
    Ifx_UReg_32Bit P2:1;              /**< \brief [2:2] Output Bit 2 (rwh) */
    Ifx_UReg_32Bit P3:1;              /**< \brief [3:3] Output Bit 3 (rwh) */
    Ifx_UReg_32Bit P4:1;              /**< \brief [4:4] Output Bit 4 (rwh) */
    Ifx_UReg_32Bit P5:1;              /**< \brief [5:5] Output Bit 5 (rwh) */
    Ifx_UReg_32Bit P6:1;              /**< \brief [6:6] Output Bit 6 (rwh) */
    Ifx_UReg_32Bit P7:1;              /**< \brief [7:7] Output Bit 7 (rwh) */
    Ifx_UReg_32Bit P8:1;              /**< \brief [8:8] Output Bit 8 (rwh) */
    Ifx_UReg_32Bit P9:1;              /**< \brief [9:9] Output Bit 9 (rwh) */
    Ifx_UReg_32Bit P10:1;             /**< \brief [10:10] Output Bit 10 (rwh) */
    Ifx_UReg_32Bit P11:1;             /**< \brief [11:11] Output Bit 11 (rwh) */
    Ifx_UReg_32Bit P12:1;             /**< \brief [12:12] Output Bit 12 (rwh) */
    Ifx_UReg_32Bit P13:1;             /**< \brief [13:13] Output Bit 13 (rwh) */
    Ifx_UReg_32Bit P14:1;             /**< \brief [14:14] Output Bit 14 (rwh) */
    Ifx_UReg_32Bit P15:1;             /**< \brief [15:15] Output Bit 15 (rwh) */
    Ifx_UReg_32Bit reserved_16:16;    /**< \brief [31:16] \internal Reserved */
} Ifx_P_OUT_Bits;

/** \brief Port n Pin Controller Select Register */
typedef struct _Ifx_P_PCSR_Bits
{
    Ifx_UReg_32Bit SEL0:1;            /**< \brief [0:0] Output Select for Pin 0 (rw) */
    Ifx_UReg_32Bit SEL1:1;            /**< \brief [1:1] Output Select for Pin 1 (rw) */
    Ifx_UReg_32Bit SEL2:1;            /**< \brief [2:2] Output Select for Pin 2 (rw) */
    Ifx_UReg_32Bit SEL3:1;            /**< \brief [3:3] Output Select for Pin 3 (rw) */
    Ifx_UReg_32Bit SEL4:1;            /**< \brief [4:4] Output Select for Pin 4 (rw) */
    Ifx_UReg_32Bit SEL5:1;            /**< \brief [5:5] Output Select for Pin 5 (rw) */
    Ifx_UReg_32Bit SEL6:1;            /**< \brief [6:6] Output Select for Pin 6 (rw) */
    Ifx_UReg_32Bit SEL7:1;            /**< \brief [7:7] Output Select for Pin 7 (rw) */
    Ifx_UReg_32Bit SEL8:1;            /**< \brief [8:8] Output Select for Pin 8 (rw) */
    Ifx_UReg_32Bit SEL9:1;            /**< \brief [9:9] Output Select for Pin 9 (rw) */
    Ifx_UReg_32Bit SEL10:1;           /**< \brief [10:10] Output Select for Pin 10 (rw) */
    Ifx_UReg_32Bit SEL11:1;           /**< \brief [11:11] Output Select for Pin 11 (rw) */
    Ifx_UReg_32Bit SEL12:1;           /**< \brief [12:12] Output Select for Pin 12 (rw) */
    Ifx_UReg_32Bit SEL13:1;           /**< \brief [13:13] Output Select for Pin 13 (rw) */
    Ifx_UReg_32Bit SEL14:1;           /**< \brief [14:14] Output Select for Pin 14 (rw) */
    Ifx_UReg_32Bit SEL15:1;           /**< \brief [15:15] Output Select for Pin 15 (rw) */
    Ifx_UReg_32Bit reserved_16:15;    /**< \brief [30:16] \internal Reserved */
    Ifx_UReg_32Bit LCK:1;             /**< \brief [31:31] Lock Status (rh) */
} Ifx_P_PCSR_Bits;

/** \brief Port n Pin Function Decision Control Register */
typedef struct _Ifx_P_PDISC_Bits
{
    Ifx_UReg_32Bit PDIS0:1;           /**< \brief [0:0] Pin Function Decision Control for Pin 0 (rw) */
    Ifx_UReg_32Bit PDIS1:1;           /**< \brief [1:1] Pin Function Decision Control for Pin 1 (rw) */
    Ifx_UReg_32Bit PDIS2:1;           /**< \brief [2:2] Pin Function Decision Control for Pin 2 (rw) */
    Ifx_UReg_32Bit PDIS3:1;           /**< \brief [3:3] Pin Function Decision Control for Pin 3 (rw) */
    Ifx_UReg_32Bit PDIS4:1;           /**< \brief [4:4] Pin Function Decision Control for Pin 4 (rw) */
    Ifx_UReg_32Bit PDIS5:1;           /**< \brief [5:5] Pin Function Decision Control for Pin 5 (rw) */
    Ifx_UReg_32Bit PDIS6:1;           /**< \brief [6:6] Pin Function Decision Control for Pin 6 (rw) */
    Ifx_UReg_32Bit PDIS7:1;           /**< \brief [7:7] Pin Function Decision Control for Pin 7 (rw) */
    Ifx_UReg_32Bit PDIS8:1;           /**< \brief [8:8] Pin Function Decision Control for Pin 8 (rw) */
    Ifx_UReg_32Bit PDIS9:1;           /**< \brief [9:9] Pin Function Decision Control for Pin 9 (rw) */
    Ifx_UReg_32Bit PDIS10:1;          /**< \brief [10:10] Pin Function Decision Control for Pin 10 (rw) */
    Ifx_UReg_32Bit PDIS11:1;          /**< \brief [11:11] Pin Function Decision Control for Pin 11 (rw) */
    Ifx_UReg_32Bit PDIS12:1;          /**< \brief [12:12] Pin Function Decision Control for Pin 12 (rw) */
    Ifx_UReg_32Bit PDIS13:1;          /**< \brief [13:13] Pin Function Decision Control for Pin 13 (rw) */
    Ifx_UReg_32Bit PDIS14:1;          /**< \brief [14:14] Pin Function Decision Control for Pin 14 (rw) */
    Ifx_UReg_32Bit PDIS15:1;          /**< \brief [15:15] Pin Function Decision Control for Pin 15 (rw) */
    Ifx_UReg_32Bit reserved_16:16;    /**< \brief [31:16] \internal Reserved */
} Ifx_P_PDISC_Bits;

/** \brief Port n Pad Driver Mode Register 0 */
typedef struct _Ifx_P_PDR0_Bits
{
    Ifx_UReg_32Bit PD0:2;             /**< \brief [1:0] Pad Driver Mode for Pin 0 (rw) */
    Ifx_UReg_32Bit PL0:2;             /**< \brief [3:2] Pad Level Selection for Pin 0 (rw) */
    Ifx_UReg_32Bit PD1:2;             /**< \brief [5:4] Pad Driver Mode for Pin 1 (rw) */
    Ifx_UReg_32Bit PL1:2;             /**< \brief [7:6] Pad Level Selection for Pin 1 (rw) */
    Ifx_UReg_32Bit PD2:2;             /**< \brief [9:8] Pad Driver Mode for Pin 2 (rw) */
    Ifx_UReg_32Bit PL2:2;             /**< \brief [11:10] Pad Level Selection for Pin 2 (rw) */
    Ifx_UReg_32Bit PD3:2;             /**< \brief [13:12] Pad Driver Mode for Pin 3 (rw) */
    Ifx_UReg_32Bit PL3:2;             /**< \brief [15:14] Pad Level Selection for Pin 3 (rw) */
    Ifx_UReg_32Bit PD4:2;             /**< \brief [17:16] Pad Driver Mode for Pin 4 (rw) */
    Ifx_UReg_32Bit PL4:2;             /**< \brief [19:18] Pad Level Selection for Pin 4 (rw) */
    Ifx_UReg_32Bit PD5:2;             /**< \brief [21:20] Pad Driver Mode for Pin 5 (rw) */
    Ifx_UReg_32Bit PL5:2;             /**< \brief [23:22] Pad Level Selection for Pin 5 (rw) */
    Ifx_UReg_32Bit PD6:2;             /**< \brief [25:24] Pad Driver Mode for Pin 6 (rw) */
    Ifx_UReg_32Bit PL6:2;             /**< \brief [27:26] Pad Level Selection for Pin 6 (rw) */
    Ifx_UReg_32Bit PD7:2;             /**< \brief [29:28] Pad Driver Mode for Pin 7 (rw) */
    Ifx_UReg_32Bit PL7:2;             /**< \brief [31:30] Pad Level Selection for Pin 7 (rw) */
} Ifx_P_PDR0_Bits;

/** \brief Port n Pad Driver Mode Register 1 */
typedef struct _Ifx_P_PDR1_Bits
{
    Ifx_UReg_32Bit PD8:2;             /**< \brief [1:0] Pad Driver Mode for Pin 8 (rw) */
    Ifx_UReg_32Bit PL8:2;             /**< \brief [3:2] Pad Level Selection for Pin 8 (rw) */
    Ifx_UReg_32Bit PD9:2;             /**< \brief [5:4] Pad Driver Mode for Pin 9 (rw) */
    Ifx_UReg_32Bit PL9:2;             /**< \brief [7:6] Pad Level Selection for Pin 9 (rw) */
    Ifx_UReg_32Bit PD10:2;            /**< \brief [9:8] Pad Driver Mode for Pin 10 (rw) */
    Ifx_UReg_32Bit PL10:2;            /**< \brief [11:10] Pad Level Selection for Pin 10 (rw) */
    Ifx_UReg_32Bit PD11:2;            /**< \brief [13:12] Pad Driver Mode for Pin 11 (rw) */
    Ifx_UReg_32Bit PL11:2;            /**< \brief [15:14] Pad Level Selection for Pin 11 (rw) */
    Ifx_UReg_32Bit PD12:2;            /**< \brief [17:16] Pad Driver Mode for Pin 12 (rw) */
    Ifx_UReg_32Bit PL12:2;            /**< \brief [19:18] Pad Level Selection for Pin 12 (rw) */
    Ifx_UReg_32Bit PD13:2;            /**< \brief [21:20] Pad Driver Mode for Pin 13 (rw) */
    Ifx_UReg_32Bit PL13:2;            /**< \brief [23:22] Pad Level Selection for Pin 13 (rw) */
    Ifx_UReg_32Bit PD14:2;            /**< \brief [25:24] Pad Driver Mode for Pin 14 (rw) */
    Ifx_UReg_32Bit PL14:2;            /**< \brief [27:26] Pad Level Selection for Pin 14 (rw) */
    Ifx_UReg_32Bit PD15:2;            /**< \brief [29:28] Pad Driver Mode for Pin 15 (rw) */
    Ifx_UReg_32Bit PL15:2;            /**< \brief [31:30] Pad Level Selection for Pin 15 (rw) */
} Ifx_P_PDR1_Bits;

/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxSfr_p_Registers_union
 * \{   */
/** \brief Port n Access Enable Register 0   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_ACCEN0_Bits B;              /**< \brief Bitfield access */
} Ifx_P_ACCEN0;

/** \brief Port n Access Enable Register 1   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_ACCEN1_Bits B;              /**< \brief Bitfield access */
} Ifx_P_ACCEN1;

/** \brief Port n Emergency Stop Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_ESR_Bits B;                 /**< \brief Bitfield access */
} Ifx_P_ESR;

/** \brief Port n Identification Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_ID_Bits B;                  /**< \brief Bitfield access */
} Ifx_P_ID;

/** \brief Port n Input Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_IN_Bits B;                  /**< \brief Bitfield access */
} Ifx_P_IN;

/** \brief Port n Input/Output Control Register 0   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_IOCR0_Bits B;               /**< \brief Bitfield access */
} Ifx_P_IOCR0;

/** \brief Port n Input/Output Control Register 12   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_IOCR12_Bits B;              /**< \brief Bitfield access */
} Ifx_P_IOCR12;

/** \brief Port n Input/Output Control Register 4   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_IOCR4_Bits B;               /**< \brief Bitfield access */
} Ifx_P_IOCR4;

/** \brief Port n Input/Output Control Register 8   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_IOCR8_Bits B;               /**< \brief Bitfield access */
} Ifx_P_IOCR8;

/** \brief Port n LVDS Pad Control Register ${x}   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_LPCR_Bits B;                /**< \brief Bitfield access */
} Ifx_P_LPCR;

/** \brief Port n Output Modification Clear Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMCR_Bits B;                /**< \brief Bitfield access */
} Ifx_P_OMCR;

/** \brief Port n Output Modification Clear Register 0   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMCR0_Bits B;               /**< \brief Bitfield access */
} Ifx_P_OMCR0;

/** \brief Port n Output Modification Clear Register 12   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMCR12_Bits B;              /**< \brief Bitfield access */
} Ifx_P_OMCR12;

/** \brief Port n Output Modification Clear Register 4   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMCR4_Bits B;               /**< \brief Bitfield access */
} Ifx_P_OMCR4;

/** \brief Port n Output Modification Clear Register 8   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMCR8_Bits B;               /**< \brief Bitfield access */
} Ifx_P_OMCR8;

/** \brief Port n Output Modification Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMR_Bits B;                 /**< \brief Bitfield access */
} Ifx_P_OMR;

/** \brief Port n Output Modification Set Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMSR_Bits B;                /**< \brief Bitfield access */
} Ifx_P_OMSR;

/** \brief Port n Output Modification Set Register 0   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMSR0_Bits B;               /**< \brief Bitfield access */
} Ifx_P_OMSR0;

/** \brief Port n Output Modification Set Register 12   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMSR12_Bits B;              /**< \brief Bitfield access */
} Ifx_P_OMSR12;

/** \brief Port n Output Modification Set Register 4   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMSR4_Bits B;               /**< \brief Bitfield access */
} Ifx_P_OMSR4;

/** \brief Port n Output Modification Set Register 8   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OMSR8_Bits B;               /**< \brief Bitfield access */
} Ifx_P_OMSR8;

/** \brief Port n Output Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_OUT_Bits B;                 /**< \brief Bitfield access */
} Ifx_P_OUT;

/** \brief Port n Pin Controller Select Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_PCSR_Bits B;                /**< \brief Bitfield access */
} Ifx_P_PCSR;

/** \brief Port n Pin Function Decision Control Register   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_PDISC_Bits B;               /**< \brief Bitfield access */
} Ifx_P_PDISC;

/** \brief Port n Pad Driver Mode Register 0   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_PDR0_Bits B;                /**< \brief Bitfield access */
} Ifx_P_PDR0;

/** \brief Port n Pad Driver Mode Register 1   */
typedef union
{
    Ifx_UReg_32Bit U;                 /**< \brief Unsigned access */
    Ifx_SReg_32Bit I;                 /**< \brief Signed access */
    Ifx_P_PDR1_Bits B;                /**< \brief Bitfield access */
} Ifx_P_PDR1;

/** \}  */

/******************************************************************************/
/** \addtogroup IfxSfr_P_Registers_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief P object */
typedef volatile struct _Ifx_P
{
       Ifx_P_OUT                           OUT;                    /**< \brief 0, Port n Output Register*/
       Ifx_P_OMR                           OMR;                    /**< \brief 4, Port n Output Modification Register*/
       Ifx_P_ID                            ID;                     /**< \brief 8, Port n Identification Register*/
       Ifx_UReg_8Bit                       reserved_C[4];          /**< \brief C, \internal Reserved */
       Ifx_P_IOCR0                         IOCR0;                  /**< \brief 10, Port n Input/Output Control Register 0*/
       Ifx_P_IOCR4                         IOCR4;                  /**< \brief 14, Port n Input/Output Control Register 4*/
       Ifx_P_IOCR8                         IOCR8;                  /**< \brief 18, Port n Input/Output Control Register 8*/
       Ifx_P_IOCR12                        IOCR12;                 /**< \brief 1C, Port n Input/Output Control Register 12*/
       Ifx_UReg_8Bit                       reserved_20[4];         /**< \brief 20, \internal Reserved */
       Ifx_P_IN                            IN;                     /**< \brief 24, Port n Input Register*/
       Ifx_UReg_8Bit                       reserved_28[24];        /**< \brief 28, \internal Reserved */
       Ifx_P_PDR0                          PDR0;                   /**< \brief 40, Port n Pad Driver Mode Register 0*/
       Ifx_P_PDR1                          PDR1;                   /**< \brief 44, Port n Pad Driver Mode Register 1*/
       Ifx_UReg_8Bit                       reserved_48[8];         /**< \brief 48, \internal Reserved */
       Ifx_P_ESR                           ESR;                    /**< \brief 50, Port n Emergency Stop Register*/
       Ifx_UReg_8Bit                       reserved_54[12];        /**< \brief 54, \internal Reserved */
       Ifx_P_PDISC                         PDISC;                  /**< \brief 60, Port n Pin Function Decision Control Register*/
       Ifx_P_PCSR                          PCSR;                   /**< \brief 64, Port n Pin Controller Select Register*/
       Ifx_UReg_8Bit                       reserved_68[8];         /**< \brief 68, \internal Reserved */
       Ifx_P_OMSR0                         OMSR0;                  /**< \brief 70, Port n Output Modification Set Register 0*/
       Ifx_P_OMSR4                         OMSR4;                  /**< \brief 74, Port n Output Modification Set Register 4*/
       Ifx_P_OMSR8                         OMSR8;                  /**< \brief 78, Port n Output Modification Set Register 8*/
       Ifx_P_OMSR12                        OMSR12;                 /**< \brief 7C, Port n Output Modification Set Register 12*/
       Ifx_P_OMCR0                         OMCR0;                  /**< \brief 80, Port n Output Modification Clear Register 0*/
       Ifx_P_OMCR4                         OMCR4;                  /**< \brief 84, Port n Output Modification Clear Register 4*/
       Ifx_P_OMCR8                         OMCR8;                  /**< \brief 88, Port n Output Modification Clear Register 8*/
       Ifx_P_OMCR12                        OMCR12;                 /**< \brief 8C, Port n Output Modification Clear Register 12*/
       Ifx_P_OMSR                          OMSR;                   /**< \brief 90, Port n Output Modification Set Register*/
       Ifx_P_OMCR                          OMCR;                   /**< \brief 94, Port n Output Modification Clear Register*/
       Ifx_UReg_8Bit                       reserved_98[8];         /**< \brief 98, \internal Reserved */
       Ifx_P_LPCR                          LPCR[8];                /**< \brief A0, Port n LVDS Pad Control Register ${x}*/
       Ifx_UReg_8Bit                       reserved_C0[56];        /**< \brief C0, \internal Reserved */
       Ifx_P_ACCEN1                        ACCEN1;                 /**< \brief F8, Port n Access Enable Register 1*/
       Ifx_P_ACCEN0                        ACCEN0;                 /**< \brief FC, Port n Access Enable Register 0*/
} Ifx_P;

#endif /*TESSY_DEFINES_H*/
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __RTL8188E_CMD_H__
#define __RTL8188E_CMD_H__

#if 0
enum cmd_msg_element_id
{
	NONE_CMDMSG_EID,
	AP_OFFLOAD_EID = 0,
	SET_PWRMODE_EID = 1,
	JOINBSS_RPT_EID = 2,
	RSVD_PAGE_EID = 3,
	RSSI_4_EID = 4,
	RSSI_SETTING_EID = 5,
	MACID_CONFIG_EID = 6,
	MACID_PS_MODE_EID = 7,
	P2P_PS_OFFLOAD_EID = 8,
	SELECTIVE_SUSPEND_ROF_CMD = 9,
	P2P_PS_CTW_CMD_EID = 32,
	MAX_CMDMSG_EID	 
};
#else
typedef enum _RTL8188E_H2C_CMD_ID
{
	//Class Common
	H2C_COM_RSVD_PAGE			=0x00,
	H2C_COM_MEDIA_STATUS_RPT	=0x01,
	H2C_COM_SCAN					=0x02,	
	H2C_COM_KEEP_ALIVE			=0x03,	
	H2C_COM_DISCNT_DECISION		=0x04,
#ifndef CONFIG_WOWLAN
	H2C_COM_WWLAN				=0x05,
#endif
	H2C_COM_INIT_OFFLOAD			=0x06,
	H2C_COM_REMOTE_WAKE_CTL	=0x07,
	H2C_COM_AP_OFFLOAD			=0x08,
	H2C_COM_BCN_RSVD_PAGE		=0x09,
	H2C_COM_PROB_RSP_RSVD_PAGE	=0x0A,

	//Class PS
	H2C_PS_PWR_MODE				=0x20,
	H2C_PS_TUNE_PARA				=0x21,
	H2C_PS_TUNE_PARA_2			=0x22,
	H2C_PS_LPS_PARA				=0x23,
	H2C_PS_P2P_OFFLOAD			=0x24,

	//Class DM
	H2C_DM_MACID_CFG				=0x40,
	H2C_DM_TXBF					=0x41,

	//Class BT
	H2C_BT_COEX_MASK				=0x60,
	H2C_BT_COEX_GPIO_MODE		=0x61,
	H2C_BT_DAC_SWING_VAL			=0x62,
	H2C_BT_PSD_RST				=0x63,
	
	//Class Remote WakeUp
#ifdef CONFIG_WOWLAN
	H2C_COM_WWLAN				=0x80,
	H2C_COM_REMOTE_WAKE_CTRL	=0x81,
	H2C_COM_AOAC_GLOBAL_INFO	=0x82,
	H2C_COM_AOAC_RSVD_PAGE		=0x83,
#endif

	//Class 
	 H2C_RESET_TSF				=0xc0,
}RTL8188E_H2C_CMD_ID;
	
#endif


struct cmd_msg_parm {
	u8 eid; //element id
	u8 sz; // sz
	u8 buf[6];
};

enum{
	PWRS
};

typedef struct _SETPWRMODE_PARM {
	u8 Mode;//0:Active,1:LPS,2:WMMPS
	//u8 RLBM:4;//0:Min,1:Max,2: User define
	u8 SmartPS_RLBM;//LPS=0:PS_Poll,1:PS_Poll,2:NullData,WMM=0:PS_Poll,1:NullData
	u8 AwakeInterval;	// unit: beacon interval
	u8 bAllQueueUAPSD;
	u8 PwrState;//AllON(0x0c),RFON(0x04),RFOFF(0x00)
} SETPWRMODE_PARM, *PSETPWRMODE_PARM;

struct H2C_SS_RFOFF_PARAM{
	u8 ROFOn; // 1: on, 0:off
	u16 gpio_period; // unit: 1024 us
}__attribute__ ((packed));


typedef struct JOINBSSRPT_PARM_88E{
	u8 OpMode;	// RT_MEDIA_STATUS
#ifdef CONFIG_WOWLAN
	u8 MacID;       // MACID
#endif //CONFIG_WOWLAN
}JOINBSSRPT_PARM_88E, *PJOINBSSRPT_PARM_88E;

typedef struct _RSVDPAGE_LOC_88E {
	u8 LocProbeRsp;
	u8 LocPsPoll;
	u8 LocNullData;
	u8 LocQosNull;
	u8 LocBTQosNull;
#ifdef CONFIG_WOWLAN
	u8 LocRemoteCtrlInfo;
	u8 LocArpRsp;
	u8 LocNbrAdv;
	u8 LocGTKRsp;
	u8 LocGTKInfo;
	u8 LocProbeReq;
	u8 LocNetList;
#endif //CONFIG_WOWLAN	
} RSVDPAGE_LOC_88E, *PRSVDPAGE_LOC_88E;


// host message to firmware cmd
void rtl8188e_set_FwPwrMode_cmd(PADAPTER padapter, u8 Mode);
void rtl8188e_set_FwJoinBssReport_cmd(PADAPTER padapter, u8 mstatus);
u8 rtl8188e_set_rssi_cmd(PADAPTER padapter, u8 *param);
u8 rtl8188e_set_raid_cmd(PADAPTER padapter, u32 mask);
void rtl8188e_Add_RateATid(PADAPTER padapter, u32 bitmap, u8* arg, u8 rssi_level);
//u8 rtl8192c_set_FwSelectSuspend_cmd(PADAPTER padapter, u8 bfwpoll, u16 period);


#ifdef CONFIG_P2P
void rtl8188e_set_p2p_ps_offload_cmd(PADAPTER padapter, u8 p2p_ps_state);
#endif //CONFIG_P2P

void CheckFwRsvdPageContent(PADAPTER padapter);
void rtl8188e_set_FwMediaStatus_cmd(PADAPTER padapter, u16 mstatus_rpt );

#ifdef CONFIG_TSF_RESET_OFFLOAD
//u8 rtl8188e_reset_tsf(_adapter *padapter, u8 reset_port);
int reset_tsf(PADAPTER Adapter, u8 reset_port );
#endif	// CONFIG_TSF_RESET_OFFLOAD

#define H2C_8188E_RSVDPAGE_LOC_LEN      5
#define H2C_8188E_AOAC_RSVDPAGE_LOC_LEN 7

#ifdef CONFIG_WOWLAN
typedef struct _SETWOWLAN_PARM{
	u8		mode;
	u8		gpio_index;
	u8		gpio_duration;
	u8		second_mode;
	u8		reserve;
}SETWOWLAN_PARM, *PSETWOWLAN_PARM;

typedef struct _SETAOAC_GLOBAL_INFO{
        u8              pairwiseEncAlg;
        u8              groupEncAlg;
}SETAOAC_GLOBAL_INFO, *PSETAOAC_GLOBAL_INFO;

#define eqMacAddr(a,b)						( ((a)[0]==(b)[0] && (a)[1]==(b)[1] && (a)[2]==(b)[2] && (a)[3]==(b)[3] && (a)[4]==(b)[4] && (a)[5]==(b)[5]) ? 1:0 )
#define cpMacAddr(des,src)					((des)[0]=(src)[0],(des)[1]=(src)[1],(des)[2]=(src)[2],(des)[3]=(src)[3],(des)[4]=(src)[4],(des)[5]=(src)[5])
#define cpIpAddr(des,src)					((des)[0]=(src)[0],(des)[1]=(src)[1],(des)[2]=(src)[2],(des)[3]=(src)[3])

//
// ARP packet
//
// LLC Header
#define GET_ARP_PKT_LLC_TYPE(__pHeader) 					ReadEF2Byte( ((u8*)(__pHeader)) + 6)

//ARP element
#define GET_ARP_PKT_OPERATION(__pHeader) 					ReadEF2Byte( ((u8*)(__pHeader)) + 6)
#define GET_ARP_PKT_SENDER_MAC_ADDR(__pHeader, _val) 		cpMacAddr((u8*)(_val), ((u8*)(__pHeader))+8)
#define GET_ARP_PKT_SENDER_IP_ADDR(__pHeader, _val) 		cpIpAddr((u8*)(_val), ((u8*)(__pHeader))+14)
#define GET_ARP_PKT_TARGET_MAC_ADDR(__pHeader, _val) 		cpMacAddr((u8*)(_val), ((u8*)(__pHeader))+18)

#define SET_ARP_PKT_HW(__pHeader, __Value)  				WriteEF2Byte( ((u8*)(__pHeader)) + 0, __Value)
#define SET_ARP_PKT_PROTOCOL(__pHeader, __Value)  			WriteEF2Byte( ((u8*)(__pHeader)) + 2, __Value)
#define SET_ARP_PKT_HW_ADDR_LEN(__pHeader, __Value)  		WriteEF1Byte( ((u8*)(__pHeader)) + 4, __Value)
#define SET_ARP_PKT_PROTOCOL_ADDR_LEN(__pHeader, __Value)  	WriteEF1Byte( ((u8*)(__pHeader)) + 5, __Value)
#define SET_ARP_PKT_OPERATION(__pHeader, __Value) 			WriteEF2Byte( ((u8*)(__pHeader)) + 6, __Value)
#define SET_ARP_PKT_SENDER_MAC_ADDR(__pHeader, _val) 		cpMacAddr(((u8*)(__pHeader))+8, (u8*)(_val))
#define SET_ARP_PKT_SENDER_IP_ADDR(__pHeader, _val) 		cpIpAddr(((u8*)(__pHeader))+14, (u8*)(_val))
#define SET_ARP_PKT_TARGET_MAC_ADDR(__pHeader, _val) 		cpMacAddr(((u8*)(__pHeader))+18, (u8*)(_val))
#define SET_ARP_PKT_TARGET_IP_ADDR(__pHeader, _val) 		cpIpAddr(((u8*)(__pHeader))+24, (u8*)(_val))

#define FW_WOWLAN_FUN_EN				BIT(0)
#define FW_WOWLAN_PATTERN_MATCH			BIT(1)
#define FW_WOWLAN_MAGIC_PKT				BIT(2)
#define FW_WOWLAN_UNICAST				BIT(3)
#define FW_WOWLAN_ALL_PKT_DROP			BIT(4)
#define FW_WOWLAN_GPIO_ACTIVE			BIT(5)
#define FW_WOWLAN_REKEY_WAKEUP			BIT(6)
#define FW_WOWLAN_DEAUTH_WAKEUP			BIT(7)

#define FW_WOWLAN_GPIO_WAKEUP_EN		BIT(0)
#define FW_FW_PARSE_MAGIC_PKT			BIT(1)

#define FW_WOWLAN_KEEP_ALIVE_EN			BIT(0)
#define FW_WOWLAN_KEEP_ALIVE_PKT_TYPE	BIT(2)

#define FW_REMOTE_WAKE_CTRL_EN			BIT(0)
#define FW_ARP_EN						BIT(1)
#define FW_REALWOWLAN_EN				BIT(5)
#define FW_WOW_FW_UNICAST_EN			BIT(7)

#define FW_ADOPT_USER					BIT(1)

void rtl8188es_set_wowlan_cmd(_adapter* padapter, u8 enable);
void SetFwRelatedForWoWLAN8188ES(_adapter* padapter, u8 bHostIsGoingtoSleep);
#endif//CONFIG_WOWLAN

//---------------------------------------------------------------------------------------------------------//
//----------------------------------    H2C CMD CONTENT    --------------------------------------------------//
//---------------------------------------------------------------------------------------------------------//
//_RSVDPAGE_LOC_CMD_0x00
#define SET_8188E_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(__pH2CCmd, __Value)     SET_BITS_TO_LE_1BYTE(__pH2CCmd, 0, 8, __Value)
#define SET_8188E_H2CCMD_RSVDPAGE_LOC_PSPOLL(__pH2CCmd, __Value)            SET_BITS_TO_LE_1BYTE((__pH2CCmd)+1, 0, 8, __Value)
#define SET_8188E_H2CCMD_RSVDPAGE_LOC_NULL_DATA(__pH2CCmd, __Value)     SET_BITS_TO_LE_1BYTE((__pH2CCmd)+2, 0, 8, __Value)
#define SET_8188E_H2CCMD_RSVDPAGE_LOC_QOS_NULL_DATA(__pH2CCmd, __Value)     SET_BITS_TO_LE_1BYTE((__pH2CCmd)+3, 0, 8, __Value)

// AOAC_RSVDPAGE_LOC_0x83
#define SET_8188E_H2CCMD_AOAC_RSVDPAGE_LOC_REMOTE_WAKE_CTRL_INFO(__pH2CCmd, __Value)        SET_BITS_TO_LE_1BYTE((__pH2CCmd), 0, 8, __Value)
#define SET_8188E_H2CCMD_AOAC_RSVDPAGE_LOC_ARP_RSP(__pH2CCmd, __Value)                  SET_BITS_TO_LE_1BYTE((__pH2CCmd)+1, 0, 8, __Value)

#endif//__RTL8188E_CMD_H__



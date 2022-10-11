#include <linux/ioctl.h> 


#define pci429_IOC_MAGIC 'k'

#define IOCTL_RJ   			_IOWR(pci429_IOC_MAGIC,100, unsigned int)
#define IOCTL_INIT			_IOWR(pci429_IOC_MAGIC,101, unsigned int)
#define IOCTL_STOP 			_IOWR(pci429_IOC_MAGIC,102, unsigned int)
#define IOCTL_DAN_SO			_IOWR(pci429_IOC_MAGIC,103, unsigned int)
#define IOCTL_WRITE_PRM_G		_IOWR(pci429_IOC_MAGIC,104, unsigned int)
#define IOCTL_READ_PRM_SS		_IOWR(pci429_IOC_MAGIC,105, unsigned int)
#define IOCTL_READ_PRM_BT		_IOWR(pci429_IOC_MAGIC,106, unsigned int)
#define IOCTL_DAN_SI			_IOWR(pci429_IOC_MAGIC,107, unsigned int)
#define IOCTL_READ_Z			_IOWR(pci429_IOC_MAGIC,108, unsigned int)
#define IOCTL_SET_DO			_IOWR(pci429_IOC_MAGIC,109, unsigned int)
#define IOCTL_GET_DI			_IOWR(pci429_IOC_MAGIC,110, unsigned int)
#define IOCTL_SET_RI			_IOWR(pci429_IOC_MAGIC,112, unsigned int)
#define IOCTL_GET_RI			_IOWR(pci429_IOC_MAGIC,113, unsigned int)
#define IOCTL_SET_RD			_IOWR(pci429_IOC_MAGIC,114, unsigned int)
#define IOCTL_GET_RD			_IOWR(pci429_IOC_MAGIC,115, unsigned int)
#define IOCTL_SET_RA			_IOWR(pci429_IOC_MAGIC,116, unsigned int)
#define IOCTL_GET_RJ			_IOWR(pci429_IOC_MAGIC,117, unsigned int)
#define IOCTL_SET_RM			_IOWR(pci429_IOC_MAGIC,118, unsigned int)
#define IOCTL_READ_MEM			_IOWR(pci429_IOC_MAGIC,119, unsigned int)
#define IOCTL_WRITE_MEM			_IOWR(pci429_IOC_MAGIC,120, unsigned int)
#define IOCTL_TAB_SO_G			_IOWR(pci429_IOC_MAGIC,121, unsigned int)
#define IOCTL_TAB_SO_F			_IOWR(pci429_IOC_MAGIC,122, unsigned int)
#define IOCTL_TAB_SI			_IOWR(pci429_IOC_MAGIC,123, unsigned int)
#define IOCTL_STOP_CH			_IOWR(pci429_IOC_MAGIC,124, unsigned int)
#define IOCTL_PUSK_SO			_IOWR(pci429_IOC_MAGIC,125, unsigned int)
#define IOCTL_PUSK_SI			_IOWR(pci429_IOC_MAGIC,126, unsigned int)
#define IOCTL_GET_RFI			_IOWR(pci429_IOC_MAGIC,111, unsigned int)
#define IOCTL_GET_SER_NUMBER		_IOWR(pci429_IOC_MAGIC,127, unsigned int)
#define IOCTL_INT			_IOWR(pci429_IOC_MAGIC,128, unsigned int)
#define IOCTL_GET_RFI_INT		_IOWR(pci429_IOC_MAGIC,129, unsigned int)

/*
#define LNX_PCI429		_IOWR( pci429_IOC_MAGIC, 130, unsigned int)
#define LNX_PCI429_START 	_IOWR( pci429_IOC_MAGIC, 131, unsigned int)
#define LNX_PCI429_EXIT		_IOWR( pci429_IOC_MAGIC, 132, unsigned int)
#define LNX_PCI429_INIT 	_IOWR( pci429_IOC_MAGIC, 133, unsigned int)
#define LNX_PCI429_STOP 	_IOWR( pci429_IOC_MAGIC, 134, unsigned int)
#define LNX_PCI429_READ_MEM 	_IOWR( pci429_IOC_MAGIC, 135, unsigned int)
#define LNX_PCI429_WRITE_MEM 	_IOWR( pci429_IOC_MAGIC, 136, unsigned int)
#define LNX_PCI429_READ_RD 	_IOWR( pci429_IOC_MAGIC, 137, unsigned int)
#define LNX_PCI429_WRITE_RD 	_IOWR( pci429_IOC_MAGIC, 138, unsigned int)
#define LNX_PCI429_SET_DO 	_IOWR( pci429_IOC_MAGIC, 139, unsigned int)
#define LNX_PCI429_GET_DI 	_IOWR( pci429_IOC_MAGIC, 140, unsigned int)
#define LNX_PCI429_SET_RM 	_IOWR( pci429_IOC_MAGIC, 141, unsigned int)
#define LNX_PCI429_GET_RJ 	_IOWR( pci429_IOC_MAGIC, 142, unsigned int)
#define LNX_PCI429_SET_RD 	_IOWR( pci429_IOC_MAGIC, 143, unsigned int)
#define LNX_PCI429_GET_RD 	_IOWR( pci429_IOC_MAGIC, 144, unsigned int)
#define LNX_PCI429_SET_RA 	_IOWR( pci429_IOC_MAGIC, 145, unsigned int)
#define LNX_PCI429_GET_RI 	_IOWR( pci429_IOC_MAGIC, 146, unsigned int)
#define LNX_PCI429_SET_RI 	_IOWR( pci429_IOC_MAGIC, 147, unsigned int)
#define LNX_PCI429_DAN_SO 	_IOWR( pci429_IOC_MAGIC, 148, unsigned int)
#define LNX_PCI429_WRITE_PRM_G 	_IOWR( pci429_IOC_MAGIC, 149, unsigned int)
#define LNX_PCI429_DAN_SI 	_IOWR( pci429_IOC_MAGIC, 150, unsigned int)
#define LNX_PCI429_READ_PRM_BT 	_IOWR( pci429_IOC_MAGIC, 151, unsigned int)
#define LNX_PCI429_READ_PRM_SS 	_IOWR( pci429_IOC_MAGIC, 152, unsigned int)
#define LNX_PCI429_TAB_SI 	_IOWR( pci429_IOC_MAGIC, 153, unsigned int)
#define LNX_PCI429_TAB_SO_F 	_IOWR( pci429_IOC_MAGIC, 154, unsigned int)
#define LNX_PCI429_TAB_SO_G 	_IOWR( pci429_IOC_MAGIC, 155, unsigned int)
#define LNX_PCI429_PUSK_SO 	_IOWR( pci429_IOC_MAGIC, 156, unsigned int)
#define LNX_PCI429_PUSK_SI 	_IOWR( pci429_IOC_MAGIC, 157, unsigned int)
#define LNX_PCI429_STOP_CH 	_IOWR( pci429_IOC_MAGIC, 158, unsigned int)
#define LNX_PCI429_READ_Z 	_IOWR( pci429_IOC_MAGIC, 159, unsigned int)
#define LNX_PCI429_GET_RFI 	_IOWR( pci429_IOC_MAGIC, 160, unsigned int)
#define LNX_PCI429_INIT_INT 	_IOWR( pci429_IOC_MAGIC, 161, unsigned int)
#define LNX_PCI429_RFI_INT 	_IOWR( pci429_IOC_MAGIC, 162, unsigned int)

*/
#define LNX_PCI429_INIT 	_IOWR( pci429_IOC_MAGIC, 130, unsigned int)
#define LNX_PCI429_STOP 	_IO( pci429_IOC_MAGIC, 131)
#define LNX_PCI429_INIT_INT 	_IOWR( pci429_IOC_MAGIC, 132,  int)
#define LNX_PCI429_RFI_INT 	_IOWR( pci429_IOC_MAGIC, 133, unsigned int)
#define LNX_PCI429_GET_INT2 	_IOWR( pci429_IOC_MAGIC, 134, unsigned int)
#define LNX_PCI429_RESET_INT	_IO( pci429_IOC_MAGIC, 135)
#define LNX_PCI429_SO_O_PARAM 	_IOWR( pci429_IOC_MAGIC, 136, unsigned int)
#define LNX_PCI429_SO_O_PUSK 	_IOWR( pci429_IOC_MAGIC, 137, unsigned int)
#define LNX_PCI429_SO_STATE 	_IOWR( pci429_IOC_MAGIC, 138, unsigned int)
#define LNX_PCI429_SO_C_PUSK 	_IOWR( pci429_IOC_MAGIC, 139, unsigned int)
#define LNX_PCI429_SO_STOP 	_IOWR( pci429_IOC_MAGIC, 140, unsigned int)
#define LNX_PCI429_SO_C_PARAM 	_IOWR( pci429_IOC_MAGIC, 141, unsigned int)
#define LNX_PCI429_SO_G_PARAM_B	_IOWR( pci429_IOC_MAGIC, 142, unsigned int)
#define LNX_PCI429_SO_G_CHANAL 	_IOWR( pci429_IOC_MAGIC, 143, unsigned int)
#define LNX_PCI429_SO_G_PARAM 	_IOWR( pci429_IOC_MAGIC, 144, unsigned int)
#define LNX_PCI429_SO_G_PUSK 	_IOWR( pci429_IOC_MAGIC, 145, unsigned int)
#define LNX_PCI429_SI_A_PUSK 	_IOWR( pci429_IOC_MAGIC, 146, unsigned int)
#define LNX_PCI429_SI_STOP 	_IOWR( pci429_IOC_MAGIC, 147, unsigned int)
#define LNX_PCI429_SI_F_PUSK	_IOWR( pci429_IOC_MAGIC, 148, unsigned int)
#define LNX_PCI429_GET_SN 	_IOWR( pci429_IOC_MAGIC, 149, unsigned int)
#define LNX_PCI429_GET_PARAM 	_IOWR( pci429_IOC_MAGIC, 150, unsigned int)
#define LNX_PCI429_GET_DI 	_IOWR( pci429_IOC_MAGIC, 151, unsigned int)
#define LNX_PCI429_SET_DO 	_IOWR( pci429_IOC_MAGIC, 152, unsigned int)
#define LNX_PCI429_CLR_DO 	_IOWR( pci429_IOC_MAGIC, 153, unsigned int)
#define LNX_PCI429_SET_DI_INTR 	_IOWR( pci429_IOC_MAGIC, 154, unsigned int)
#define LNX_PCI429_SI_STATE 	_IOWR( pci429_IOC_MAGIC, 155, unsigned int)
#define LNX_PCI429_SI_PARAM 	_IOWR( pci429_IOC_MAGIC, 156, unsigned int)
#define LNX_PCI429_SI_BUFER 	_IOWR( pci429_IOC_MAGIC, 157, unsigned int)
#define LNX_PCI429_STOP_INT 	_IOWR( pci429_IOC_MAGIC, 158, unsigned int)
#define LNX_PCI429_CLEAR_DI_INTR 	_IOWR( pci429_IOC_MAGIC, 159, unsigned int)

#define pci429_IOC_MAXNR 60



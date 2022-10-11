#include <sys/ioctl.h>

//
//		
#define SET_RM(Data,ii) Data[0x1100]=(unsigned short)ii
#define SET_RM_BITS(Data,k4,k3,k2,k1,m4,m3,m2,m1,s,t,e,m,r) Data[0x1100]=(unsigned short)((k4<<15)|(k3<<14)|(k2<<13)|(k1<<12)|\
	(m4<<11)|(m3<<10)|(m2<<9)|(m1<<8)|(s<<7)|\
	(t<<3)|(e<<2)|(m<<1)|(r))
#define SET_RM_BIT_R(Data) Data[0x1100]=(unsigned short)(Data[0x1100]|1)
#define CLR_RM_BIT_R(Data) Data[0x1100]=(unsigned short)(Data[0x1100]&0xfffe)
#define SET_RM_BIT_M(Data) Data[0x1100]=(unsigned short)(Data[0x1100]|2)
#define CLR_RM_BIT_M(Data) Data[0x1100]=(unsigned short)(Data[0x1100]&0xfffd)
#define SET_RM_BIT_E(Data) Data[0x1100]=(unsigned short)(Data[0x1100]|4)
#define CLR_RM_BIT_E(Data) Data[0x1100]=(unsigned short)(Data[0x1100]&0xfffb)
#define SET_RM_BIT_T(Data) Data[0x1100]=(unsigned short)(Data[0x1100]|8)
#define CLR_RM_BIT_T(Data) Data[0x1100]=(unsigned short)(Data[0x1100]&0xfff7)
#define SET_RM_BIT_S(Data) Data[0x1100]=(unsigned short)(Data[0x1100]|128)
#define CLR_RM_BIT_S(Data) Data[0x1100]=(unsigned short)(Data[0x1100]&0xff7f)
#define SET_RM_BIT_M1(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|256)
#define SET_RM_BIT_M2(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|512)
#define SET_RM_BIT_M3(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|1024)
#define SET_RM_BIT_M4(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|2048)
#define SET_RM_BIT_K1(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|4096)
#define SET_RM_BIT_K2(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|8192)
#define SET_RM_BIT_K3(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|16384)
#define SET_RM_BIT_K4(Data)Data[0x1100]=(unsigned short)(Data[0x1100]|32768)
#define CLR_RM_BIT_M1(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0xfeff)
#define CLR_RM_BIT_M2(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0xfdff)
#define CLR_RM_BIT_M3(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0xfbff)
#define CLR_RM_BIT_M4(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0xf7ff)
#define CLR_RM_BIT_K1(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0xefff)
#define CLR_RM_BIT_K2(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0xdfff)
#define CLR_RM_BIT_K3(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0xbfff)
#define CLR_RM_BIT_K4(Data)Data[0x1100]=(unsigned short)(Data[0x1100]&0x7fff)

#define WRITE_RM(hARINC,Data) ioctl(hARINC,IOCTL_SET_RM,Data)


//
#define GET_RM(Data,ii) ii=Data[0x1100]

//
#define GET_SN(hARINC,Data,ii) ioctl(hARINC,IOCTL_GET_SER_NUMBER,Data);\
					ii=Data[0x1850]
//
#define GET_RJ(hARINC,Data,ii) ioctl(hARINC,IOCTL_GET_RJ,Data);\
					ii=Data[0x1101]


#define GET_RJ_M(Data,ii) ii=Data[0x1101]


//
#define GET_RD(hARINC,Data,ii) ioctl(hARINC,IOCTL_GET_RD,Data);\
					ii=Data[0x1105]

#define SET_RD(hARINC,Data,ii) Data[0x1105]=ii;\
	ioctl(hARINC,IOCTL_SET_RD,Data)
					

//
#define SET_RA(hARINC,Data,ii) Data[0x1105]=ii;\
	ioctl(hARINC,IOCTL_SET_RA,Data)



// 
#define READ_RA_CH(hARINC,Data,adr,ch) Data[0x1108]=adr;\
					Data[0x1109]=ch;\
				  	ioctl(hARINC,IOCTL_READ_MEM,Data)

// 
#define WRITE_RA_CH(hARINC,Data,adr,ch) Data[0x110a]=adr;\
					Data[0x110b]=ch;\
					ioctl(hARINC,IOCTL_WRITE_MEM,Data)
					
		

//		
//   
#define GET_RC_SI_M(hARINC,Data,nc,ii) Data[0x1108]=0x1f+nc;\
		Data[0x1109]=1;\
		ioctl(hARINC,IOCTL_READ_MEM,Data);\
		ii=Data[0x1f+nc]

//  
#define GET_RC_SO_M(hARINC,Data,nc,ii) Data[0x1108]=0x27+nc;\
		Data[0x1109]=1;\
	  	ioctl(hARINC,IOCTL_READ_MEM,Data);\
		ii=Data[0x27+nc]

//
#define GET_RS_SI_M(hARINC,Data,nc,ii) Data[0x1108]=0xf+nc;\
		Data[0x1109]=1;\
	  	ioctl(hARINC,IOCTL_READ_MEM,Data);\
		ii=Data[0xf+nc]
  
//
#define GET_RS_SO_M(hARINC,Data,nc,ii) Data[0x1108]=0x17+nc;\
		Data[0x1109]=1;\
	  	ioctl(hARINC,IOCTL_READ_MEM,Data);\
		ii=Data[0x17+nc]
		
		




//
//
#define SET_RF_SI(Data,i1,i2,i3,i4,i5,i6,i7,i8,o1,o2,o3,o4,o5,o6,o7,o8)Data[0]=i1|(o1<<2);\
  Data[1]=i2|(o2<<2); Data[2]=i3|(o3<<2); Data[3]=i4|(o4<<2);\
  Data[4]=i5|(o5<<2); Data[5]=i6|(o6<<2); Data[6]=i7|(o7<<2); Data[7]=i8|(o8<<2)
//   
#define SET_RF_SO(Data,i1,i2,i3,i4,i5,i6,i7,i8,o1,o2,o3,o4,o5,o6,o7,o8)Data[8]=i1|(o1<<2);\
  Data[9]=i2|(o2<<2); Data[10]=i3|(o3<<2); Data[11]=i4|(o4<<2);\
  Data[12]=i5|(o5<<2); Data[13]=i6|(o6<<2); Data[14]=i7|(o7<<2); Data[15]=i8|(o8<<2)

// 
#define SET_RF_SI_N(Data,i1,i2,i3,i4,i5,i6,i7,i8)Data[0]=i1;\
  Data[1]=i2; Data[2]=i3; Data[3]=i4;\
  Data[4]=i5; Data[5]=i6; Data[6]=i7; Data[7]=i8
//  
#define SET_RF_SO_N(Data,i1,i2,i3,i4,i5,i6,i7,i8)Data[8]=i1;\
  Data[9]=i2; Data[10]=i3; Data[11]=i4;\
  Data[12]=i5; Data[13]=i6; Data[14]=i7; Data[15]=i8

//
//
#define GET_RF_SI(Data,i1,i2,i3,i4,i5,i6,i7,i8,o1,o2,o3,o4,o5,o6,o7,o8) i1=Data[0]&3; o1=Data[0]>>2&1;\
  i2=Data[1]&3; o2=Data[1]>>2&1; i3=Data[2]&3; o3=Data[2]>>2&1; i4=Data[3]&3; o4=Data[3]>>2&1; \
  i5=Data[4]&3; o5=Data[4]>>2&1; i6=Data[5]&3; o6=Data[5]>>2&1;\
  i7=Data[6]&3; o7=Data[6]>>2&1; i8=Data[7]&3; o8=Data[7]>>2&1
//  
#define GET_RF_SO(Data,i1,i2,i3,i4,i5,i6,i7,i8,o1,o2,o3,o4,o5,o6,o7,o8) i1=Data[8]&3; o1=Data[8]>>2&1;\
  i2=Data[9]&3; o2=Data[9]>>2&1; i3=Data[10]&3; o3=Data[10]>>2&1; i4=Data[11]&3; o4=Data[11]>>2&1; \
  i5=Data[12]&3; o5=Data[12]>>2&1; i6=Data[13]&3; o6=Data[13]>>2&1;\
  i7=Data[14]&3; o7=Data[14]>>2&1; i8=Data[15]&3; o8=Data[15]>>2&1


//
#define SET_SO_GLBL(Data,i1,i2,i3,i4,i5,i6,i7,i8) Data[0x1010]=i1&1;\
	Data[0x1011]=i2&1;Data[0x1012]=i3&1;Data[0x1013]=i4&1;Data[0x1014]=i5&1;\
	Data[0x1015]=i6&1;Data[0x1016]=i7&1;Data[0x1017]=i8&1

//
#define GET_SO_GLBL(Data,nc,i) i=Data[0x100f+nc]


//
#define INIT_ARINC(hARINC,Data) ioctl(hARINC,IOCTL_INIT,Data)


//
#define ARINC_STOP(hARINC,Data)	ioctl(hARINC,IOCTL_STOP,Data)


//
#define WRITE_PRM_G(hARINC,Data,np,li) Data[0x5001+(np-1)*2]=(unsigned short)(((li)>>16)&0xffff);\
	Data[0x5000+(np-1)*2]=(unsigned short)(li&0xffff);\
	Data[0x1110]=(unsigned short)(0x5000+(np-1)*2);\
	ioctl(hARINC,IOCTL_WRITE_PRM_G,Data)

//
#define WRITE_PRM_F(hARINC,Data,nc,nb,np,li) Data[0x5001+nb*0x2000+Data[0x1018+nc-1]+(np-1)*2]=(unsigned short)(((li)>>16)&0xffff);\
	Data[0x5000+nb*0x2000+Data[0x1018+nc-1]+(np-1)*2]=(unsigned short)(li&0xffff);\
	Data[0x1110]=(unsigned short)(0x5000+nb*0x2000+Data[0x1018+nc-1]+(np-1)*2);\
	ioctl(hARINC,IOCTL_WRITE_PRM_G,Data)


//
  #define WRITE_PRM(hARINC,Data,nc,nb,np,li) Data[0x5001+nb*0x2000+Data[0x1018+nc-1]+(np-1)*2]=(unsigned short)(((li)>>16)&0xffff);\
	Data[0x5000+nb*0x2000+Data[0x1018+nc-1]+(np-1)*2]=(unsigned short)(li&0xffff);\
    Data[0x1110]=(unsigned short)(0x5000+nb*0x2000+Data[0x1018+nc-1]+(np-1)*2);\
	ioctl(hARINC,IOCTL_DAN_SO ,Data)
	

//
#define READ_PRM_BT(hARINC,Data,nc,nb,np,li) Data[0x1110]=0x4000+nb*0x2000+(nc-1)*0x200+(np)*2;\
	ioctl(hARINC,IOCTL_READ_PRM_BT ,Data);\
	li=((Data[0x4001+nb*0x2000+(nc-1)*0x200+(np)*2]&0xffff)<<16)|\
   	(Data[0x4000+nb*0x2000+(nc-1)*0x200+(np)*2]&0xffff)
   
//
#define READ_PRM_SS(hARINC,Data,nc,nb,np,li) Data[0x1110]=0x4000+nb*0x2000+(nc-1)*0x200+(np)*2;\
    	Data[0x110c]=nc;\
	ioctl(hARINC,IOCTL_READ_PRM_SS ,Data);\
	li=((Data[0x4001+nb*0x2000+(nc-1)*0x200+(np)*2]&0xffff)<<16)|\
	(Data[0x4000+nb*0x2000+(nc-1)*0x200+(np)*2]&0xffff)


//
#define READ_PRM(hARINC,Data,nc,nb,np,li) Data[0x1110]=0x4000+nb*0x2000+(nc-1)*0x200+(np)*2;\
	Data[0x110c]=nc;\
	ioctl(hARINC,IOCTL_DAN_SI ,Data);\
	li=((Data[0x4001+nb*0x2000+(nc-1)*0x200+(np)*2]&0xffff)<<16)|\
	(Data[0x4000+nb*0x2000+(nc-1)*0x200+(np)*2]&0xffff)


//
#define READ_PRM_Z(hARINC,Data,nc,nb,np) Data[0x1110]=0x4000+nb*0x2000+(nc-1)*0x200+(np)*2;\
	ioctl(hARINC,IOCTL_READ_Z ,Data)
	


// 
#define SET_DO(hARINC,Data,ii) Data[0x1106]=(ii);\
	ioctl(hARINC,IOCTL_SET_DO ,Data)
	
#define GET_DI(hARINC,Data,ii)  ioctl(hARINC,IOCTL_GET_DI ,Data);\
			ii=Data[0x1107]	  
			

//
#define WRITE_RI(hARINC,Data) ioctl(hARINC,IOCTL_SET_RI,Data)


//
#define READ_RI(hARINC,Data,i16,i15,i14,i13,i12,i11,i10,i9,i8,i7,i6,i5,i4,i3,i2,i1) \
	ioctl(hARINC,IOCTL_GET_RI,Data);\
    i16=Data[0x1104]>>15&1; i15=Data[0x1104]>>14&1; i14=Data[0x1104]>>13&1;\
	i13=Data[0x1104]>>12&1; i12=Data[0x1104]>>11&1; i11=Data[0x1104]>>10&1;\
	i10=Data[0x1104]>>9&1;   i9=Data[0x1104]>>8&1;  i8=Data[0x1104]>>7&1;\
	i7 =Data[0x1104]>>6&1;   i6=Data[0x1104]>>5&1;  i5=Data[0x1104]>>4&1;\
	i4 =Data[0x1104]>>3&1;   i3=Data[0x1104]>>2&1;  i2=Data[0x1104]>>1&1; i1=Data[0x1104]&1

#define READ_RI_WORD(hARINC,Data,i) \
	ioctl(hARINC,IOCTL_GET_RI,Data);\
    i=Data[0x1104]


//
#define SET_SO_TAB_Z(Data,nc,nb,i) for (i=0;i<256;i++) {Data[0x2800+nb*0x1000+(nc-1)*0x100+i]=0;}
#define SET_SO_TAB_F(Data,nc,nb,i,i1) Data[0x2800+nb*0x1000+(nc-1)*0x100+(i-1)]=i1<<13
#define SET_SO_DAN_RC_F(hARINC,Data,nc,nb,cikl,start,number) if(number<1) {Data[0x1102]=3;}\
		else {\
		Data[0x1020+nb*0x18+(nc-1)*3+1]=cikl;Data[0x1020+nb*0x18+(nc-1)*3+2]=start;\
		Data[0x2800+nb*0x1000+(nc-1)*0x100+(start-1)+(number-1)]=Data[0x2800+nb*0x1000+(nc-1)*0x100+(start-1)+(number-1)]|0x8001;\
		Data[0x110c]=nc;Data[0x110d]=nb;\
		ioctl( hARINC,IOCTL_TAB_SO_F,Data);\
		if (Data[0x1102]==0){Data[0x1020+nb*0x18+(nc-1)*3]=1;}}


//
#define SET_SO_TAB_G(Data,nc,i,i1,i2) Data[0x2800+(nc-1)*0x100+(i-1)]=(i2<<13)|0x1000|((i1-1)<<1)
#define SET_SO_DAN_RC_G(hARINC,Data,nc,number) if(number<1) {Data[0x1102]=3;}\
		else {\
		Data[0x1020+(nc-1)*3+1]=0;Data[0x1020+(nc-1)*3+2]=1;\
		Data[0x2800+(nc-1)*0x100+(number-1)]=(unsigned short)(Data[0x2800+(nc-1)*0x100+(number-1)]|(0x8001));\
		Data[0x110c]=nc; Data[0x110b]=number;\
		ioctl( hARINC,IOCTL_TAB_SO_G,Data);\
		if(Data[0x1102]==0){Data[0x1020+(nc-1)*3]=1;} }


//
#define GET_SO_DAN_RC(Data,nc,nb,cikl,start) cikl=Data[0x1020+nb*0x18+(nc-1)*3+1];start=Data[0x1020+nb*0x18+(nc-1)*3+2]


//
#define SET_SI_TAB_Z(Data,nc,nb,i) for (i=0;i<256;i++) {Data[0x2000+nb*0x1000+(nc-1)*0x100+i]=0;}
#define SET_SI_TAB_E(Data,nc,nb,i,e) Data[0x2000+nb*0x1000+(nc-1)*0x100+(i)]=(e&1)<<14				
#define SET_SI_TAB_M(Data,nc,nb,i,m) Data[0x2000+nb*0x1000+(nc-1)*0x100+(i)]=\
		(unsigned short)(Data[0x2000+nb*0x1000+(nc-1)*0x100+(i)]|((m&1)<<15))
#define SET_SI_TAB_KM(Data,nc,nb,i,km) Data[0x2000+nb*0x1000+(nc-1)*0x100+(i)]=\
		(unsigned short)(Data[0x2000+nb*0x1000+(nc-1)*0x100+(i)]|(km&1))
#define SET_SI_TAB(hARINC,Data,nc,nb) 	Data[0x1050+nb*0x8+(nc-1)]=1;\
		Data[0x110c]=(unsigned short)nc;\
		Data[0x110d]=(unsigned short)nb;\
		ioctl( hARINC,IOCTL_TAB_SI,Data)


//
#define STOP_SO(hARINC,Data,nc) Data[0x110e]=(nc-1)|8;\
		ioctl ( hARINC,IOCTL_STOP_CH,Data)


//
#define STOP_SI(hARINC,Data,nc) Data[0x110e]=(nc-1);\
		ioctl ( hARINC,IOCTL_STOP_CH,Data)


// 
#define PUSK_SO(hARINC,Data,nc,nb,m,e) Data[0x27+nc]=(unsigned short)(((m&1)<<15)|((e&1)<<14)|\
((nb&1)<<13)|((nb&1)<<12)|0x500|((Data[0x1020+nb*0x18+(nc-1)*3+1]&1)<<9)|(Data[0x1020+nb*0x18+(nc-1)*3+2]&0xff-1));\
		Data[0x110e]=nc; Data[0x110f]=nb; \
				  ioctl ( hARINC,IOCTL_PUSK_SO,Data);\
				  if(Data[0x1102]==0)Data[0x1020+nb*24+(nc-1)*3]=0
//
#define PUSK_SO_ST(hARINC,Data,nc,nb,m,cikl,start,number,i) for (i=0;i<256;i++) {Data[0x2800+nb*0x1000+(nc-1)*0x100+i]=0;}\
	if(number<1) {Data[0x1102]=2;}\
	else {\
    Data[0x1020+nb*0x18+(nc-1)*3+1]=cikl;\
	Data[0x1020+nb*0x18+(nc-1)*3+2]=start;\
	Data[0x2800+nb*0x1000+(nc-1)*0x100+(start-1)+(number-1)]=\
	Data[0x2800+nb*0x1000+(nc-1)*0x100+(start-1)+(number-1)]|0x8001;\
	Data[0x110c]=(unsigned short)nc;\
	Data[0x110d]=(unsigned short)nb;\
	ioctl ( hARINC,IOCTL_TAB_SO_F,Data);\
	if(Data[0x1102]==0){Data[0x1020+nb*0x18+(nc-1)*3]=1;\
	Data[0x27+nc]=(unsigned short)(((m&1)<<15)|\
		((nb&1)<<13)|((nb&1)<<12)|0x500|((Data[0x1020+nb*0x18+(nc-1)*3+1]&1)<<9)|\
		(Data[0x1020+(nb)*0x18+(nc-1)*3+2]&0xff-1));\
	Data[0x110e]=(unsigned short)nc;\
	Data[0x110f]=(unsigned short)nb;\
	ioctl ( hARINC,IOCTL_PUSK_SO,Data);\
	if(Data[0x1102]==0)Data[0x1020+nb*24+(nc-1)*3]=0;\
	}\
	}
	

//
#define PUSK_SI(hARINC,Data,nc,nb,m,ap) Data[0x1f+nc]=((m&1)<<15)|((ap&1)<<9)|\
((nb&1)<<13)|((nb&1)<<12)|0x500;\
		Data[0x110e]=nc; Data[0x110f]=nb;\
		ioctl( hARINC,IOCTL_PUSK_SI,Data);\
				  if(Data[0x1102]==0)Data[0x1050+nb*8+nc-1]=0
//
#define PUSK_SI_ST(hARINC,Data,nc,nb,ap, i)	for (i=0;i<256;i++)	{Data[0x2000+nb*0x1000+(nc-1)*0x100+i]=0;}\
	Data[0x1050+nb*0x8+(nc-1)]=1;\
	Data[0x110c]=(unsigned short)nc;\
	Data[0x110d]=(unsigned short)nb;\
	ioctl ( hARINC,IOCTL_TAB_SI,Data);\
	if(Data[0x1102]==0){Data[0x1f+nc]=(unsigned short)(((ap&1)<<9)|((nb&1)<<13)|((nb&1)<<12)|0x500);\
	Data[0x110e]=(unsigned short)nc; Data[0x110f]=(unsigned short)nb;\
	ioctl ( hARINC,IOCTL_PUSK_SI,Data);\
	if(Data[0x1102]==0)Data[0x1050+nb*8+nc-1]=0;}



//
#define GET_ERROR(Data,err) err=Data[0x1102]




//
#define INT_SET(hARINC,Data) Data[0x1900]= (unsigned short)getpid();\
 	ioctl(hARINC,IOCTL_INT,Data);\
	

	


//
#define READ_RFI_WORD(hARINC,Data,i) \
	ioctl(hARINC,IOCTL_GET_RFI,Data);\
    	i=Data[0x1700]

#define READ_RFI_INT(hARINC,Data,i) \
	ioctl(hARINC,IOCTL_GET_RFI_INT,Data);\
    	i=Data[0x1701]


	

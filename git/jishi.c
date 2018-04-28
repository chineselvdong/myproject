		#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]={0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint qian,bai,shi,ge;
sbit key0=P2^0;
sbit key1=P2^1;
sbit key2=P2^2;
sbit key3=P2^3;
sbit key4=P2^4;
sbit w1=P3^4;	//��������P3^2�ڣ��������P3^4,5,6,7�ڣ�������P2��
sbit w2=P3^5;	//����û����������ֻ�ܸ��͵�ƽѡͨ�����
sbit w3=P3^6;
sbit w4=P3^7;
uint sum=0,num=0;

void delayms(uint ms)
{
	uint i,j;
	for(i=110;i>0;i--)
		for(j=ms;j>0;j--);
}
void shuizi()
{ge=sum%10;
 shi=(sum%100)/10;
 bai=(sum%1000)/100;
 qian=sum/1000;
}


void keyscan()
{
	if(key0==0)
	 {
	 	delayms(5);
		if(key0==0)
		{
		sum=sum+1000;
		while(!key0);
		}
	 }

	  if(key1==0)
	 {
	 	delayms(5);
		if(key1==0)
		{
		sum=sum+100;
		while(!key1);
		}
	 }

	 if(key2==0)
	 {
	 	delayms(5);
		if(key2==0)
		{
		sum=sum+10;
		while(!key2);
		}
	 }
	 if(key3==0)
	 {
	 	delayms(5);
		if(key3==0)
		{
		sum=sum+1;
		while(!key3);
		}
	 }
}


void display(int qian,int bai,int shi,int ge)	 //��ʾ����
{	w1=0;	//ѡͨ
	P0=table[qian];//P0����ʾ�����  	 
	delayms(1);//��ʱ������ͣ��
	w1=1;//�رղ��صĻ�����һ�θ�ֵ���ڶ�������ܵ�һ��Ҳ����ʾ������ݻ���
	//ע��˿���������û�������������������ܵĿ����������Ա�����ʱ
	//��ҿ������Բ�����ʱ���������Ĺ����ǰ�������ʱ���棬ͨ�������ر�
	 //�������������������Կ��ع��̲�����ʱ
	w2=0;		  
	P0=table[bai]+0x80;
		 
	delayms(1);
	w2=1;

	w3=0;
	P0=table[shi];
	delayms(1);
	w3=1;

	w4=0;
	P0=table[ge];   	
	delayms(1);
	w4=1;
}






void main()
{
	uchar flag=1;
	while(flag)
	{
		keyscan();
		shuizi();
	    display(qian, bai, shi, ge);
		if(key4==0)
		{
			delayms(5);
			if(key4==0)
			{
				EA=1;
				flag=0;
				while(!key4);
			}
		}
	}


  	TMOD=0x01;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	ET0=1;
	TR0=1;

	while(1)
	{
		display(qian, bai, shi, ge);
	if(sum==0)
	{
	P3=0xfb;
	EA=0;
	}
	}
 
}
 
 void T0_time() interrupt 1
 {
 		TH0=(65536-1000)/256;
		TL0=(65536-1000)%256;
		num++;
		if(num>=10)
		{
			num=0;
			sum--;
			ge=sum%10;
			shi=(sum%100)/10;
		    bai=(sum%1000)/100;
			qian=sum/1000;
		}
 }
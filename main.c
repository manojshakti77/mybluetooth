#include"p1.h"
#include"hcicmd.h"
#include"hcievent.h"
#include<pthread.h>

int sfd;
struct hci_filter nf;
int hci_cmd_count;

int socket_creation(void);
int linux_setting_filter(unsigned short int opcode,unsigned char event_code);

void *thread_fun(void *arg)
{
	int retval;
	char buf[260];
	while(1)
	{
	    while ((retval = read(sfd, buf, sizeof(buf))) < 0) 
		{
		if (errno == EAGAIN || errno == EINTR)
			continue;
		break;
		}
		printf("EVENT RECEIVED\n");
    	hci_rec_event(buf);
	}
}


int main(void)
{
	unsigned short int ogf,ocf,opcode;
	int retval;
//	char buf[260];
	sockaddr_hci a;
	unsigned char *ptr;
	pthread_t tid;


	sfd = socket_creation();	
	
	pthread_create(&tid,NULL,thread_fun,NULL);
	/* Sending the RESET command */
	hci_send_cmd_reset(sfd);
	retval = linux_setting_filter(0x0C03,0x0E);
	if(retval == 0)
		return 0;
	sleep(1);
	
#if 0
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
	if(retval <0)
		return 0;
#endif


	retval = hci_send_cmd_hcifilter(sfd);
	if(retval <0)
		return 0;
	retval = linux_setting_filter(0x0C05,0x0E);
	if(retval == 0)
		return 0;
	sleep(1);

#if 0
	/*Reading from HCI*/
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
#endif

	retval = hci_send_cmd_setcod(sfd);
	if(retval <0)
		return 0;
	retval = linux_setting_filter(0x0C24,0x0E);
        if(retval == 0)
                return 0;
	sleep(1);

#if 0
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
#endif

	
	retval = hci_send_cmd_setdisc(sfd);
	if(retval <0)
		return 0;
	retval = linux_setting_filter(0x0C1A,0x0E);
	if(retval == 0)
		return 0;
	sleep(1);

#if 0
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
#endif	

	retval = hci_send_cmd_spp(sfd);
	if(retval <0)
		return 0;
	retval = linux_setting_filter(0x0C56,0x0E);
	if(retval == 0)
		return 0;
	sleep(1);

#if 0
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
#endif

	/*-----Sending the Inquiry Enable Command-------*/
	retval = hci_send_cmd_inquiry(sfd);
	if(retval <0)
		return 0;
	retval = linux_setting_filter(0x0401,0x02);
    if(retval == 0)
        return 0;
    sleep(1);
	

    retval = linux_setting_filter(0x0401,0x01);
    if(retval == 0)
        return 0;
    sleep(1);
	

	
	while(1);
	
	return 1;
}

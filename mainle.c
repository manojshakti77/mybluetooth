#include"p1.h"
#include"hcicmdle.h"
#include"hcicmd.h"

int sfd;
struct hci_filter nf;

int hci_rec_event(unsigned char *buf);
int linux_setting_filter(unsigned short int opcode,unsigned char event_code);
int socket_creation(void);

int main(void)
{
	unsigned short int ogf,ocf,opcode;
	int retval;
	char buf[260];
	sockaddr_hci a;
	unsigned char *ptr;


	sfd = socket_creation();	

	/*--------------- Sending the RESET command -------------------*/
	hci_send_cmd_reset(sfd);
	retval = linux_setting_filter(0x0C03,0x0E);
	if(retval == 0)
		return 0;
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
	if(retval <0)
		return 0;
	/*--------------------------------------------------------------*/

	/*------------------Sending LE Set ADV DATA---------------------*/
	retval = hci_send_cmd_le_adv_data(sfd);
	if(retval <0)
		return 0;
	retval = linux_setting_filter(0x2006,0x0E);
	if(retval == 0)
		return 0;
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
	/*--------------------------------------------------------------*/


	/*-------------------Setting ADV Enable--------------------*/
	retval = hci_send_cmd_set_adv_enable(sfd);
	if(retval <0)
		return 0;
	retval = linux_setting_filter(0x0C24,0x0E);
        if(retval == 0)
                return 0;
	while ((retval = read(sfd, buf, sizeof(buf))) < 0) {
                        if (errno == EAGAIN || errno == EINTR)
                                continue;
                        break;
                }
	hci_rec_event(buf);
	/*--------------------------------------------------------------*/
	
	
	return 1;
}

int num_cmds = 0;
int hci_rec_event(unsigned char *buf)
{
        switch(buf[0])/*Type of command*/
        {
        case 0x01:
                printf("COMMAND\n");
                break;
        case 0x04:
                printf("EVENT PACKET\n");
                if(buf[1] == 0x0e)//Command complete
                {
                        printf("Length.......0x%02X\n",buf[2]);
                        num_cmds = buf[3];
                        printf("Number of hci command can execute....0x%02X\n",buf[3]);
                        printf("Number of hci command can execute....%d\n",num_cmds);
                        printf("OPCODE=0x%02X%02X\n",buf[4],buf[5]);
                        printf("Status=0x%02X\n",buf[6]);
                }
                break;
        default :
                printf("Default packet.....0x%02X\n",buf[0]);
                break;
        }

}

#include"p1.h"

extern int sfd;
extern struct hci_filter nf;

/*Socket Creation*/

int socket_creation(void)
{
	int sfd;
	sockaddr_hci a;
	sfd=socket(AF_BLUETOOTH,SOCK_RAW,BTPROTO_HCI);
        if(sfd < 0)
        {
                perror("sfd");
                return 0;
        }
        memset(&a, 0, sizeof(a));
        a.hci_family=AF_BLUETOOTH;
        a.hci_dev=0;
        if (bind(sfd, (struct sockaddr *) &a, sizeof(a)) < 0)
        {
                perror("bind");
                return 0;
        }
	return sfd;

}
int linux_setting_filter(unsigned short int opcode,unsigned char event_code)
{

	/* Linux related(Setting the filter characterstics */
	hci_filter_clear(&nf);
	hci_filter_set_ptype(HCI_EVENT_PKT,  &nf);
	hci_filter_set_event(EVT_CMD_STATUS, &nf);
	hci_filter_set_event(EVT_CMD_COMPLETE, &nf);
	hci_filter_set_event(EVT_LE_META_EVENT, &nf);
	hci_filter_set_event(event_code, &nf);
	hci_filter_set_opcode(opcode, &nf);

	if (setsockopt(sfd,SOL_HCI, HCI_FILTER, &nf, sizeof(nf)) < 0)
	{
		perror("setsockopt");
        return 0;
	}
	return 1;
}

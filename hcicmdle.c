#include "p1.h"
int hci_send_cmd_le_adv_data(int sfd)
{
	hci_set_le_adv_data le_adv_data;
    le_adv_data.pkt_type = HCI_CMD_PKT;
    le_adv_data.opcode_lsb = 0x20;
    le_adv_data.opcode_msb = 0x08;
    le_adv_data.plen=32;
    le_adv_data.adv_len = 5;
    strncpy(le_adv_data.adv_data,"MANOJ",5);
   
	return (write(sfd,&le_adv_data,sizeof(le_adv_data)));	
}

int hci_send_cmd_set_adv_enable(int sfd)
{
	hci_set_le_adv set_le_adv;
	set_le_adv.pkt_type = HCI_CMD_PKT;
    set_le_adv.opcode_lsb = 0x20;
    set_le_adv.opcode_msb = 0x0A;
    set_le_adv.plen = 1;
    set_le_adv.le_adv_enable = 0x01;

	return (write(sfd,&set_le_adv,sizeof(set_le_adv)));
}

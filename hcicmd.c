#include"p1.h"

int hci_send_cmd_inquiry(int sfd)
{
	hci_set_inquiry hci_set_inquiry;
	hci_set_inquiry.pkt_type= HCI_CMD_PKT;
	hci_set_inquiry.opcode_lsb = 0x04;
	hci_set_inquiry.opcode_msb = 0x01;
	hci_set_inquiry.plen = 0x05;
	hci_set_inquiry.lap[2] = 0x9E;
	hci_set_inquiry.lap[1] = 0x8B;
	hci_set_inquiry.lap[0] = 0x33;
	hci_set_inquiry.inquiry_length = 0x30;
	hci_set_inquiry.num_responses = 0x07;
	return (write(sfd,&hci_set_inquiry,sizeof(hci_set_inquiry)));
}
int hci_send_cmd_reset(int sfd)
{
	
	hci_command_reset cmd_reset;
	cmd_reset.pkt_type= HCI_CMD_PKT;
	cmd_reset.opcode_lsb = 0x0C;
	cmd_reset.opcode_msb = 0x03;
	cmd_reset.plen = 0x00;
	return (write(sfd,&cmd_reset,sizeof(cmd_reset)));
}

int hci_send_cmd_hcifilter(int sfd)
{
	hci_set_event_mask set_event_mask;
    
	set_event_mask.pkt_type = HCI_CMD_PKT;
    set_event_mask.opcode_lsb = 0x0C;
    set_event_mask.opcode_msb = 0x05;
    set_event_mask.plen=0x08;
    set_event_mask.set_event_mask_data[0] = 0x00;
    set_event_mask.set_event_mask_data[1] = 0x00;
    set_event_mask.set_event_mask_data[2] = 0x00;
    set_event_mask.set_event_mask_data[3] = 0x00;
    set_event_mask.set_event_mask_data[4] = 0x00;
    set_event_mask.set_event_mask_data[5] = 0x00;
    set_event_mask.set_event_mask_data[6] = 0x00;
    set_event_mask.set_event_mask_data[7] = 0x00;

    return (write(sfd,&set_event_mask,sizeof(set_event_mask)));	
}

int hci_send_cmd_setcod(int sfd)
{
	hci_set_cod set_cod;

	/*Setting the class of device*/
    set_cod.pkt_type = HCI_CMD_PKT;
    set_cod.opcode_lsb = 0x0C;
    set_cod.opcode_msb = 0x24;
    set_cod.plen = 0x03;
    set_cod.cod[0] = 0x18;
    set_cod.cod[1] = 0x04;
    set_cod.cod[2] = 0x20;
    return (write(sfd,&set_cod,sizeof(set_cod)));	
}

int hci_send_cmd_setdisc(int sfd)
{
	hci_set_scan set_scan;

	/*Setting the Device into Discoverable Mode*/
    set_scan.pkt_type = 0x01;
    set_scan.opcode_lsb = 0x0C;
    set_scan.opcode_msb = 0x1A;
    set_scan.plen = 0x01;
    set_scan.scan_param = 0x03;
    return(write(sfd,&set_scan,sizeof(set_scan)));	
}

int hci_send_cmd_spp(int sfd)
{
	hci_set_spp set_spp;
	
	/*Setting up the simple pairing mode*/
    set_spp.pkt_type = 0x01;
    set_spp.opcode_lsb = 0x0C;
    set_spp.opcode_msb = 0x56;
    set_spp.plen = 0x01;
    set_spp.spp_param = 0x01;
    return (write(sfd,&set_spp,sizeof(set_spp)));
	
}

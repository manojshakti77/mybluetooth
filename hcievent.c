#include"p1.h"
#include"hcievent.h"

extern int hci_cmd_count;

int hci_rec_event(unsigned char *buf)
{
	unsigned short int *ptr;
	int status;

        switch(buf[0])/*Type of command*/
        {
        case 0x01:
                printf("COMMAND\n");
                break;
        case 0x04:
                if(buf[1] == 0x0E)//Command complete
                {
                        hci_cmd_count = buf[3];
						printf("STATUS....0x%02X\n",buf[6]);
						switch(*(unsigned short int *)(buf+4))
						{
							case 0x0C03 : status = hci_reset_event(buf+6);
											return status;
							case 0X0C05 : status = hci_set_filter_event(buf+6);
											return status;
							case 0x0C24 : status = hci_set_cod_event(buf+6);
											return status;
							case 0x0C1A : status = hci_set_disc_event(buf+6);
											return status;
							case 0x0C56 : status = hci_set_spp_event(buf+6);
                                            return status;
							
								default : 	printf("Default EVENT\n");
											printf("Length.......0x%02X\n",buf[2]);
                        					printf("Number of hci command can execute....0x%02X\n",buf[3]);
                        					printf("OPCODE=0x%02X%02X\n",buf[5],buf[4]);
                        					printf("Status=0x%02X\n",buf[6]);
											break;
						}
                }
				else
				{
					switch(buf[1])
					{
						case 0x01 : status = hci_inquiry_complete_event(buf+3);
									return status;
						case 0x02 : status = hci_inquiry_result_event(buf+2);
									return status;
						default : printf("Unknown Event....0x%02X\n",buf[1]);
									break;
					}
				}
                break;
        default :
                printf("Default packet.....0x%02X\n",buf[0]);
                break;
        }

}

int hci_inquiry_complete_event(unsigned char *ptr)
{
	if(!ptr[0])
    {
        printf("Inquriry complete COMMAND SUCCESSFUL.....0x%02X\n",ptr[6]);
        return 0;
    }
    else
    {
        printf("Inquiry complete COMMAND UNSUCCESSFUL.....0x%02X\n",ptr[6]);
        return 1;
    }
}
int hci_inquiry_result_event(unsigned char *ptr)
{
	int num_reponses = ptr[0];
	int i,j;
	printf("Number of responses......%d  %d\n",ptr[0],num_reponses);
	unsigned char *bd_addr;
//	unsigned char *page_rept_mode;

	bd_addr = &ptr[1];
//	page_rept_mode = &ptr[(6 * num_reponses) + 1];
	for(i = 0;i < num_reponses;i++)
	{
		for(j = 0;j < 6;j++)
		{
			printf("%02X ",bd_addr[i+j]);
		} 
		printf("\n");
	}
	
}
int hci_reset_event(unsigned char *ptr)
{
	if(!ptr[0])
    {
		printf("RESET COMMAND SUCCESSFUL.....0x%02X\n",ptr[0]);
		return 0;
    }
    else
    {
		printf("RESET COMMAND UNSUCCESSFUL.....0x%02X\n",ptr[0]);
		return 1;
	}
}
int hci_set_filter_event(unsigned char *ptr)
{
    if(!ptr[0])
    {
        printf("Set Filter COMMAND SUCCESSFUL....0x%02X\n",ptr[0]);
        return 0;
    }
    else
    {
        printf("Set Filter UNSUCCESSFUL....0x%02X\n",ptr[0]);
        return 1;
    }
}
int hci_set_cod_event(unsigned char *ptr)
{
    if(!ptr[0])
    {
        printf("Set COD COMMAND SUCCESSFUL....0x%02X\n",ptr[0]);
        return 0;
    }
    else
    {
        printf("Set COD UNSUCCESSFUL....0x%02X\n",ptr[0]);
        return 1;
    }
}
int hci_set_disc_event(unsigned char *ptr)
{
    if(!ptr[0])
    {
        printf("Set DISCOVERABLE COMMAND SUCCESSFUL....0x%02X\n",ptr[0]);
        return 0;
    }
    else
    {
        printf("Set DISCOVERABLE COMMAND UNSUCCESSFUL....0x%02X\n",ptr[0]);
        return 1;
    }
}
int hci_set_spp_event(unsigned char *ptr)
{
    if(!ptr[0])
    {
        printf("Set SPP COMMAND SUCCESSFUL....0x%02X\n",ptr[0]);
        return 0;
    }
    else
    {
        printf("Set SPP COMMAND UNSUCCESSFUL....0x%02X\n",ptr[0]);
        return 1;
    }
}

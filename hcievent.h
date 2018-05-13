int hci_rec_event(unsigned char *buf);
int hci_reset_event(unsigned char *ptr);
int hci_set_filter_event(unsigned char *ptr);
int hci_set_cod_event(unsigned char *ptr);
int hci_set_disc_event(unsigned char *ptr);
int hci_set_spp_event(unsigned char *ptr);
int hci_inquiry_result_event(unsigned char *ptr);
int hci_inquiry_complete_event(unsigned char *ptr);

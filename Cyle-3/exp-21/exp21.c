#include<stdio.h>
#include<stdlib.h>

int main() {
    int i, n, packet_index, ack, no_ack, choice, windowsize, sent;
    printf("The number of packets: ");
    scanf("%d", &n);
    printf("Enter window size: ");
    scanf("%d", &windowsize);
    
    while (1) {
        printf("\n1. Go-Back-N\n2. Selective Repeat\n3. Stop and Wait\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Go-Back-N
                sent = 0;
                while (1) {
                    for (i = 0; i < windowsize; i++) {
                        printf("Frame %d has been transmitted..\n", sent+1);
                        sent++;
                        if (sent == windowsize) break;
                    }
                    ack = rand() % windowsize + 1;
                    printf("Last acknowledgment received = %d\n", ack);
                    if (ack == windowsize) break;
                    else sent = ack;
                }
                break;
            case 2: // Selective Repeat
                printf("Transmission begins.. Packet size %d\n", n);
                i = 1;
                while (i <= n) {
                    printf("Sending packets from %d to %d\n", i, windowsize + i - 1);
                    for (packet_index = i; packet_index < windowsize + i; packet_index++)
                        printf("Transmission packet %d\n", packet_index);
                    no_ack = i + rand() % windowsize;
                    if (no_ack == i) {
                        printf("Acknowledged=%d\n", windowsize + i);
                        i = i + windowsize;
                        continue;
                    }
                    printf("NACK=%d\n", no_ack);
                    printf("Sending packet %d\n", no_ack);
                    printf("Acknowledged=%d\n", no_ack + 1);
                    printf("Acknowledged=%d\n", windowsize + i);
                    i = i + windowsize;
                }
                break;
            case 3: // Stop and Wait
                for (i = 1; i <= n; i++) {
                    printf("The packet sent is: %d\n", i);
                    if (rand() % 2 == 1) {
                        ack = rand() % 2;
                        if (ack == 1) 
                            printf("Acknowledgment number: %d\n", i + 1);
                        else 
                            printf("No acknowledgment number: %d\n", i + 1);
                    } else {
                        printf("Timeout, resend\n");
                        i--;
                    }
                }
                break;
            case 4:
                printf("Exited");
                exit(0);
            default:
                printf("Invalid input");
                break;
        }
    }
    return 0;
}

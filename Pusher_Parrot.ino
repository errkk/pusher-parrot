#include <SPI.h>
#include <Ethernet.h>
#include <PusherClient.h>

byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
PusherClient client;
IPAddress ip(192,168,100,101);
const int parrot = 3;
const int led = 5;


void setup() {
    pinMode(parrot, OUTPUT);
    pinMode(led, OUTPUT);

    Serial.begin(9600);
    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, ip);
    }
    else {
        Serial.println("Ethernet connected");
    }
    threeBlinks();


    if(client.connect(PUSHER_KEY)) {
        client.bind("data_recieved", dataRecieved);
        client.bind("response_sent", responseSent);
        client.subscribe("test_channel");
    }
    else {
        Serial.println("Couldn't connect to pusher");
        while(1) {
        }
    }
}

void loop() {
    if (client.connected()) {
        client.monitor();
    }
    else {
        Serial.println("Client not connected");
    }
}

void dataRecieved(String data) {
    Serial.println("Data Recieved");
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);    

}

void responseSent(String data) {
    Serial.println("Response Sent");
    digitalWrite(parrot, HIGH);
    delay(1000);
    digitalWrite(parrot, LOW);
}

void flashOnce(void) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
}

void threeBlinks(void) {
    flashOnce();
    flashOnce();
    flashOnce();
}

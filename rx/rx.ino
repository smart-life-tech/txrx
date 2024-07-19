#include <IRremote.hpp>

// Define the IR receiver pin
int recvPin = 2;

// Define the LED pins
int ledPins[] = {4, 5, 6, 7, 8}; // Adjust as needed
int ledOffPin = 9;               // Pin for "off" LED

//IRrecv irrecv(recvPin);
//decode_results results;

// Define the unique IR codes
unsigned long irCodesOn[] = {0x1FE48B7, 0x10, 0x11, 0x12, 0x13, 0x14}; // Add more codes for each "on" transmitter
unsigned long irCodeOff = 0x1FE58A7;                                   // Code for "off" transmitter
void handleData()
{
    /*
     * Print a short summary of received data
     */
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        // We have an unknown protocol here, print more info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    /*
     * !!!Important!!! Enable receiving of the next value,
     * since receiving has stopped after the end of the current received data packet.
     */
    IrReceiver.resume(); // Enable receiving of the next value

    /*
     * Finally, check the received data and perform actions according to the received command
     */
    // Check if the received code matches any "on" code
    for (int i = 0; i < 6; i++)
    {
        if (IrReceiver.decodedIRData.command == irCodesOn[i])
        {
            digitalWrite(ledPins[i], HIGH);
        }
        else
        {
            digitalWrite(ledPins[i], LOW);
        }
    }

    // Check if the received code matches the "off" code
    if (IrReceiver.decodedIRData.command == irCodeOff)
    {
        for (int i = 0; i < 5; i++)
        {
            digitalWrite(ledPins[i], LOW);
        }
        digitalWrite(ledOffPin, HIGH);
    }
    if (IrReceiver.decodedIRData.command == 0x10)
    {
        // do something
    }
    else if (IrReceiver.decodedIRData.command == 0x11)
    {
        // do something else
    }
}
void setup()
{
    Serial.begin(9600);
    IrReceiver.enableIRIn();

    // Initialize LED pins
    for (int i = 0; i < 5; i++)
    {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
    pinMode(ledOffPin, OUTPUT);
    digitalWrite(ledOffPin, LOW);
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(recvPin, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
}

void loop()
{
    if (IrReceiver.decode())
    {
        handleData();
        unsigned long receivedCode = 0;//results.value;

        // Check if the received code matches any "on" code
        for (int i = 0; i < 5; i++)
        {
            if (receivedCode == irCodesOn[i])
            {
                digitalWrite(ledPins[i], HIGH);
            }
            else
            {
                digitalWrite(ledPins[i], LOW);
            }
        }

        // Check if the received code matches the "off" code
        if (receivedCode == irCodeOff)
        {
            for (int i = 0; i < 5; i++)
            {
                digitalWrite(ledPins[i], LOW);
            }
            digitalWrite(ledOffPin, HIGH);
        }

        IrReceiver.resume(); // Receive the next value
    }
}

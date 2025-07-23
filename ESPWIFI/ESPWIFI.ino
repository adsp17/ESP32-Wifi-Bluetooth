#include <WiFi.h>
const char* ssid = "ESP32_LED";
const char* password = "12345678";

IPAddress local_ip(100, 168, 10, 1);
IPAddress gateway(192, 168, 10, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

const int ledPin = 2;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.println("ESP32 Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String req = client.readStringUntil('\r');
    client.flush();

    if (req.indexOf("/LED=ON") != -1) {
      ledState = true;
    } else if (req.indexOf("/LED=OFF") != -1) {
      ledState = false;
    }

    digitalWrite(ledPin, ledState);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>ESP32 LED Control</title>");
    client.println("<style>");
    client.println("body { font-family: Arial; display: flex; justify-content: center; align-items: center; height: 100vh; background-color: #f2f2f2; margin: 0; }");
    client.println(".container { text-align: center; background: #fff; padding: 40px; border-radius: 15px; box-shadow: 0 0 20px rgba(0,0,0,0.1); }");
    client.println("h2 { color: #333; font-size: 28px; margin-bottom: 30px; }");
    client.println("a { text-decoration: none; }");
    client.println(".btn { font-size: 24px; padding: 15px 40px; margin: 15px; border: none; border-radius: 10px; color: white; cursor: pointer; transition: background-color 0.2s ease, transform 0.1s ease; }");
    client.println(".btn-on { background-color: #4CAF50; }");
    client.println(".btn-on:hover { background-color: #45a049; }");
    client.println(".btn-on:active { background-color: #388e3c; transform: scale(0.98); }");
    client.println(".btn-off { background-color: #f44336; }");
    client.println(".btn-off:hover { background-color: #e53935; }");
    client.println(".btn-off:active { background-color: #c62828; transform: scale(0.98); }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<div class='container'>");

    client.print("<h2>LED Status: ");
    client.print(ledState ? "ON" : "OFF");
    client.println("</h2>");

    client.println("<a href=\"/LED=ON\"><button class='btn btn-on'>TURN ON</button></a>");
    client.println("<a href=\"/LED=OFF\"><button class='btn btn-off'>TURN OFF</button></a>");

    client.println("</div>");
    client.println("</body></html>");
  }
}

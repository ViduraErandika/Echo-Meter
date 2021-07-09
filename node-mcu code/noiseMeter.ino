#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "webpageCode.h";
#include <math.h> 

const int analogInPin = A0; 

ESP8266WebServer server(80);

const char* ssid = "V_Connect";
const char* password = "SanasumaSumangala";

const char* mqtt_server = "test.mosquitto.org";
const char* outTopic = "noiseOut";

void graph()
{
  int pot_val = analogRead(0);
  double decible = 20* log10( pot_val);
  String show = String(decible) + " dB";
  String value = "<html><head><meta http-equiv=\"refresh\" content=\"2\">";
  value += "<meta charset='utf-8'>";
  value += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  value += "<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC' crossorigin='anonymous'>";
  value += "<title>Noise Meter</title></head>";
  value += "<body ><nav class='navbar navbar-expand-lg navbar-dark bg-primary'>";
  value += "<div><a class='navbar-brand' href='#' style='padding-left: 20px;'>";
  value += "<img src='https://i.ibb.co/QpFw5NB/air.png' alt='' width='40' height='30'></a></div>";
  value +="<div class='container-fluid'><a class='navbar-brand' href='#'>Noise Meter</a>";
  value += "<button class='navbar-toggler' type='button' data-bs-toggle='collapse' data-bs-target='#navbarNavAltMarkup' aria-controls='navbarNavAltMarkup' aria-expanded='false' aria-label='Toggle navigation'>";
  value += "<span class='navbar-toggler-icon'></span> </button>";
  value += "<div class='collapse navbar-collapse' id='navbarNavAltMarkup'>";
  value += "<div class='navbar-nav'>";
  value += "<a class='nav-link active' aria-current='page' href='/'>Home</a></div></div>";
  value += "<div class='d-flex'>";
  value += "<a class='nav-link active text-black-50 btn btn-warning' style='font-weight: 500;' aria-current='page' href='https://node-red-iot-project-sem4.mybluemix.net/ui/#!/0?socketid=DIojaEa4vYiq2cJUAAAP'>Dashboard</a></div>";
  value += "</div></nav>";
  value += "<div style='background-color: aqua; overflow: hidden;'><img src='https://i.ibb.co/XfQw9sF/3425171.jpg' alt='' width='1920' height='1080'></div>";
  value += "<div class='col-12  text-center'  style=' top: 28%; position: absolute;padding-top: 50px; padding-bottom: 50px; padding-left: 80px; background-color: rgba(0,0,0,0.2)'  >";
  
  value += "<p  class='text-light display-2 text-truncate' style='font-weight: 400;'>Noise Value :</p>";
  value += "<a  href='javascript: void(0)'   class='btn btn-primary' style='font-size: 35px; font-weight: lighter;'><i class='mdi mdi-link-variant mr-2'></i> ";
  value += show;
  value += "</a><br><br>";
  if (decible < 50){
    value += "<a  href='javascript: void(0)'   class='btn btn-success' style='font-size: 50px; font-weight: normal; padding-left: 70px; padding-right: 70px; '><i class='mdi mdi-link-variant mr-2'></i> ";
    value += "Safe Area";
    value += "</a><br><br>";
  }else if (decible > 50){
    value += "<a  href='javascript: void(0)'   class='btn btn-danger' style='font-size: 50px; font-weight: normal; padding-left: 70px; padding-right: 70px;'><i class='mdi mdi-link-variant mr-2'></i> ";
    value += "Harmful Area";
    value += "</a><br><br>";
  }
  value += "<p  class='h1 text-white-50  text-truncate' style='font-weight: 400;'>Realtime Value Only. For Furthur Information Visit The Dashboard.</p>";
  value += "</div>  ";
  value += "<body class='d-flex flex-column'>";
  value += "<footer id='sticky-footer' class='py-4 bg-dark text-white-50'>";
  value += "<div class='container text-center'>";
  value += "<small>Copyright &copy; NoiseMeter.com</small>";
  value += "</div></footer></body>";
  value += "</body></html>";
  
  server.send(200, "text/html", value);
}
void webpage()
{
  server.send(200,"text/html", webpageCode);
}



WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMin = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", webpage);
  server.on("/graph", graph);
  server.begin();
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int soundSens = analogRead(analogInPin);

  unsigned long now = millis();
  if (now - lastMin > 1000) {
    lastMin = now;
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", soundSens);
    Serial.print("Publish value: ");
    Serial.println(msg);
    client.publish(outTopic, msg);
  }
  delay(5);
  server.handleClient();
}

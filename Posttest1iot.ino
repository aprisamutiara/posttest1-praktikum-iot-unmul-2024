#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED1 4  // Pin D2
#define LED2 12    // Pin D6

const char* ssid = "Ipppppp";       // Nama Hotspot
const char* password = "ipppahhh";    // Password Hotspot

ESP8266WebServer server(80);      //Menyatakan Webserver pada port 80
String webpage;

void setup() {  //Pengaturan Pin
  Serial.begin(9600);
  delay(100);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Connect ke Hotspot
  Serial.println();
  Serial.print("Mengkonfigurasi akses point...");

  // Mengatur WiFi 
  WiFi.mode(WIFI_AP);                      // Mode AP //mikrokontoler bisa jdi akses point
  WiFi.begin(ssid, password);               // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED) { //cara cek wifi
    delay(500);
    Serial.print("....");
  }
  
  // Print status Connect 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  
  // Isi dari Webpage && membuat halaman web
  webpage += "<h1><center> Posttest 1 IoT: Monitor LED </center></h1><br>";
  webpage += "<center> LED 1 : </center><br>";
  webpage += "<a href=\"LED1ON\"\"><center><button>Hidup</button></a><a href=\"LED1OFF\"\"><button>Mati</button></center></a><br>";
  webpage += "<center> LED 2 : </center><br>";
  webpage += "<a href=\"LED2ON\"\"><center><button>Hidup</button></a><a href=\"LED2OFF\"\"><button>Mati</button></center></a><br>";

  // Membuat file webpage (halaman web)
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });

  // Bagian ini untuk merespon perintah yang masuk 
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
  });

  server.on("/LED1OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
  });
  server.on("/LED2OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2, LOW);
  });

  server.begin();
  Serial.println("Server dijalankan");
}

void loop() {  //Perulangan Program
  server.handleClient();
}
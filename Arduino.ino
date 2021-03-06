#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>

const char* ssid ="Nombre de la red 2.4 GHZ";
const char* password ="Password";

int TMP = 0;
float temperatura=0;
int SENSOR = D2; 
bool a=false;

WiFiClient client; 

void setup() {
    pinMode(SENSOR, INPUT);
  Serial.begin(115200);
  Serial.println("DHT 11 prueba de conexión con el servidor");

  WiFi.begin(ssid, password);
  Serial.print("Conectando...");
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexión OK!");
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  EnvioDatos();
}

// rutina de envio de datos por POST
void EnvioDatos(){
  String sonido;
  temperatura = analogRead(TMP); // analogRead lee los valores del ping analogico A0.
  temperatura=(5.0 * temperatura * 100.0)/1024.0; // calibramos la temperatura con la siguiente formula
    a = false;
    if(digitalRead(SENSOR)==LOW){
    a = true;
    }
    if(a==true){sonido="Low";
    }else{sonido="High";
    }
    
  if (WiFi.status() == WL_CONNECTED){ 
     HTTPClient http;  // creo el objeto http
     String datos_a_enviar = "temperatura=" + String(temperatura) + "&sonido=" + sonido;  
       Serial.println(datos_a_enviar);
     http.begin(client,"http://192.168.100.4/EnvioDatos.php");// Poner la IP del dispositivo que vayamos a usar y la pagina adonde iran los datos
     http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    
     int codigo_respuesta = http.POST(datos_a_enviar);
       Serial.println(codigo_respuesta);
     if (codigo_respuesta>0){
      Serial.println("Código HTTP: "+ String(codigo_respuesta));
        if (codigo_respuesta == 200){
          String cuerpo_respuesta = http.getString();
          Serial.println("El servidor respondió: ");
          Serial.println(cuerpo_respuesta);
        }
     } else {
        Serial.print("Error enviado POST, código: ");
        Serial.println(codigo_respuesta);
     }
     http.end();  // libero recursos
       
  } else {
     Serial.println("Error en la conexion WIFI");
  }
  delay(10000); //espera 10s
}

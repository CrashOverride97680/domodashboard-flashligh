#include <ESP8266WiFi.h>

const char* ssid = "xxxxxxx";    //  Wi-Fi SSID
const char* password = "xxxxxxxxxxxx";  // Wi-Fi Password
int value = LOW;
int value2 = LOW;
int LED1 = 2;   // Led connesso al PIN D2
int LED2 = D2;
WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, HIGH);

  Serial.print("Mi sto connettendo al WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connesso"); 
  server.begin();  // Inizializza il server
  Serial.println("Server Attivo");

  Serial.print("Indirizzo IP del server: "); // will IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("copia e incolla questo URL per accedere al server: http://"); // Scriviamo l'indirizzo per raggiungere il server
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
}

void loop(){
  WiFiClient client = server.available();
  if (!client){
    return;
  }

  Serial.println("attendo la connessione di un client");
  while(!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  if(request.indexOf("/LED1=ON") != -1){ // Se ricevo "ON" 
    digitalWrite(LED1, LOW); // Accendo il led
    value = HIGH;
  }

  if(request.indexOf("/LED1=OFF") != -1){ // Se ricevo "OFF"
    digitalWrite(LED1, HIGH); // Turn LED OFF
    value = LOW;
  }

  if(request.indexOf("/LED2=ON") != -1){ // Se ricevo "ON" 
    digitalWrite(LED2, LOW); // Accendo il led
    value2 = HIGH;
  }

  if(request.indexOf("/LED2=OFF") != -1){ // Se ricevo "OFF"
    digitalWrite(LED2, HIGH); // Turn LED OFF
    value2 = LOW;
  }

 
//*------------------Codice HTML della pagina---------------------*//

  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE html>");
  client.println("<html lang=\"it\">");
  client.println("<head>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<!--[if IE]><meta http-equiv='X-UA-Compatible' content='IE=edge,chrome=1'><![endif]-->");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
  client.println("<title>Dashboard | Flashlight</title>");
  client.println("<meta name=\"description\" content=\"Dashboard IOT\"/>");
  client.println("<!--[if lt IE 9]><script src=\"https://cdnjs.cloudflare.com/ajax/libs/html5shiv/3.7.3/html5shiv.js\"></script><![endif]-->");
  client.println("<link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\">");
  client.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css\">");
  client.println("<style>");
  client.println("  h2{font-size: 2.25rem;text-transform: uppercase;}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body style=\"background-color: ghostwhite\">");
  client.println("<header style= \"background-color: darkturquoise; text-align: center; text-transform: uppercase; color: white; width:100%\">");
  client.println("  <h1 style=\"margin:0; padding: 20px 0; font-size: 3rem\">Dashboard</h1>");
  client.println("</header>");
  client.println("<div class=\"row container\" style=\"margin-bottom: 60px\">");
  client.println("  <div class=\"col s8\">");
  client.println("    <h2>Relè 1</h2>");
  client.println("  </div>");
  client.println("  <div class=\"col s4\">");
  if( value == LOW ){ client.println("<a class= \"waves-effect waves-light btn-large\" style=\"margin:2.3733333333rem 0 1.424rem 0\" href=\"/LED1=ON\">ON</a>");}
  if( value == HIGH ){ client.println("<a class= \"waves-effect waves-light btn-large\" style=\"margin:2.3733333333rem 0 1.424rem 0\" href=\"/LED1=OFF\">OFF</a>");}
  client.println("  </div>");
  client.println("  <div class=\"col s8\">");
  client.println("    <h2>Relè 2</h2>");
  client.println("  </div>");
  client.println("  <div class=\"col s4\">");
  if( value2 == LOW ){ client.println("<a class= \"waves-effect waves-light btn-large\" style=\"margin:2.3733333333rem 0 1.424rem 0\" href=\"/LED2=ON\">ON</a>");}
  if( value2 == HIGH ){ client.println("<a class= \"waves-effect waves-light btn-large\" style=\"margin:2.3733333333rem 0 1.424rem 0\" href=\"/LED2=OFF\">OFF</a>");}
  client.println("  </div>");
  client.println("</div>");
  client.println("<script src=\"https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js\" defer></script>");
  client.println("<footer style=\"text-align: center; color: white; background-color: #353535; position: fixed; bottom: 0;padding: 25px 0;width:100%\">");
  client.println("  <strong>Created by <a href=\"https://github.com/CrashOverride97680\" rel=\"nofollow noopener\" target=\"_blank\" title=\"Account CrashOverride97680 github\">CrashOverride97680</a> github user</strong>");
  client.println("</footer>");
  client.println("</body>");
  client.println("</html>");
  delay(200);
  Serial.println("Client disconnesso");
  Serial.println("");
}

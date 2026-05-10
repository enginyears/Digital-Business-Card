/*
 * ============================================
 *   ESP32 DIGITAL BUSINESS CARD
 *   Beginner Level — Heavily Commented
 *   No external components needed!
 * ============================================
 * 
 * What this does:
 *   The ESP32 creates its own WiFi network.
 *   When someone connects to that WiFi,
 *   they open a browser and see your
 *   digital business card — instantly.
 *
 * No internet needed. No phone app needed.
 * Just a $4 chip doing all the work.
 * ============================================
 */

// These lines "include" built-in tools we need
// Think of them like importing apps on your phone
#include <Arduino.h>   // Basic Arduino functions
#include <WiFi.h>      // WiFi control functions
#include <WebServer.h> // Lets ESP32 act like a website server

// ─────────────────────────────────────────────
// ✏️  EDIT THIS SECTION — Make it yours!
// ─────────────────────────────────────────────

const char* CARD_NAME    = "Hrithik";
const char* CARD_TITLE   = "Enginyears";
const char* CARD_EMAIL   = "enginyears@gmail.com";
const char* CARD_PHONE   = "+911234567890";
const char* CARD_INSTA   = "@enginyears.me";
const char* CARD_GITHUB  = "github.com/enginyears";
const char* CARD_LINK    = "enginyears.com";

// This is the name of the WiFi network your ESP32 will create
const char* WIFI_NAME    = "My Digital Card";

// This is the password people need to connect to it
//const char* WIFI_PASS    = "helloworld";

// ─────────────────────────────────────────────
// The HTML page your card will show
// This is the actual webpage — CSS + HTML in one string
// ─────────────────────────────────────────────
// We use String so we can insert variables like CARD_NAME
// The F() wrapper saves memory by keeping strings in flash
// ─────────────────────────────────────────────

String buildCardPage() {
  String page = "";
  page += "<!DOCTYPE html><html><head>";
  page += "<meta charset='UTF-8'>";
  // This makes it look right on mobile screens
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<title>" + String(CARD_NAME) + "</title>";

  // All the styling (colours, fonts, layout)
  page += "<style>";
  page += "* { margin:0; padding:0; box-sizing:border-box; }";
  page += "body { background:#0d0d0d; font-family:Georgia,serif; min-height:100vh;";
  page += "  display:flex; align-items:center; justify-content:center; padding:20px; }";
  page += ".card { background:#141414; border:1px solid #333; border-radius:16px;";
  page += "  padding:36px 28px; max-width:360px; width:100%; text-align:center; }";
  page += ".avatar { width:80px; height:80px; border-radius:50%; background:linear-gradient(135deg,#f5a623,#f02fc2);";
  page += "  margin:0 auto 18px; display:flex; align-items:center; justify-content:center;";
  page += "  font-size:2em; }";
  page += ".name { color:#ffffff; font-size:1.5em; margin-bottom:6px; letter-spacing:0.5px; }";
  page += ".title { color:#888; font-size:0.85em; margin-bottom:28px; letter-spacing:1px; text-transform:uppercase; }";
  page += ".divider { border:none; border-top:1px solid #222; margin-bottom:22px; }";
  page += ".link { display:block; padding:12px 16px; margin-bottom:10px; border-radius:10px;";
  page += "  background:#1e1e1e; color:#ccc; text-decoration:none; font-size:0.82em;";
  page += "  letter-spacing:0.5px; border:1px solid #2a2a2a; transition:background 0.2s; }";
  page += ".link span { float:left; margin-right:10px; }";
  page += ".footer { margin-top:22px; font-size:0.6em; color:#333; letter-spacing:2px; text-transform:uppercase; }";
  page += "</style></head><body>";

  // The actual card content — using the variables you edited above
  page += "<div class='card'>";
  page += "  <div class='avatar'>👤</div>";
  page += "  <div class='name'>" + String(CARD_NAME) + "</div>";
  page += "  <div class='title'>" + String(CARD_TITLE) + "</div>";
  page += "  <hr class='divider'>";
  page += "  <a class='link' href='mailto:" + String(CARD_EMAIL) + "'><span>✉️</span>" + String(CARD_EMAIL) + "</a>";
  page += "  <a class='link' href='tel:" + String(CARD_PHONE) + "'><span>📞</span>" + String(CARD_PHONE) + "</a>";
  page += "  <a class='link' href='https://instagram.com/" + String(CARD_INSTA).substring(1) + "'><span>📸</span>" + String(CARD_INSTA) + "</a>";
  page += "  <a class='link' href='https://wa.me/" + String(CARD_PHONE) + "?text=Hello'><span>💬</span> WhatsApp</a>";
  page += "  <a class='link' href='https://" + String(CARD_GITHUB) + "'><span>💻</span>" + String(CARD_GITHUB) + "</a>";
  page += "  <a class='link' href='https://" + String(CARD_LINK) + "'><span>🔗</span>" + String(CARD_LINK) + "</a>";
  page += "  <div class='footer'>Powered by ESP32 ⚡</div>";
  page += "</div>";
  page += "</body></html>";

  return page;
}

// ─────────────────────────────────────────────
// Create the web server on port 80
// Port 80 is the standard port for websites
// ─────────────────────────────────────────────
WebServer server(80);

// ─────────────────────────────────────────────
// setup() runs ONCE when ESP32 turns on
// ─────────────────────────────────────────────
void setup() {
  // Start serial monitor so we can see messages (9600 is the speed)
  Serial.begin(115200);
  Serial.println("Starting up...");

  // Tell ESP32 to be an Access Point (AP)
  // This means it creates its OWN WiFi network
  WiFi.mode(WIFI_AP);

  // Start broadcasting the WiFi network with name + password
  WiFi.softAP(WIFI_NAME); //, WIFI_PASS);

  // Print the IP address to serial monitor so you know it's working
  // By default this is always 192.168.4.1
  Serial.println("WiFi started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Tell the server: when someone visits the root page ("/")
  // run this function and send them the card HTML
  server.on("/", []() {
    server.send(200, "text/html", buildCardPage());
  });

  // Start the web server
  server.begin();
  Serial.println("Server started! Connect to: " + String(WIFI_NAME));
  Serial.println("Then open: http://192.168.4.1");
}

// ─────────────────────────────────────────────
// loop() runs FOREVER after setup()
// We just need to keep the server listening
// for new visitors — handleClient() does that
// ─────────────────────────────────────────────
void loop() {
  server.handleClient();
}

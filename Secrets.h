#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32_LDR2"                         //change this
 
const char WIFI_SSID[] = "alterwin";               //change this
const char WIFI_PASSWORD[] = "123456788";           //change this
const char AWS_IOT_ENDPOINT[] = "ac4v4pkzew2n-ats.iot.ap-southeast-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
HERE CERTIFICATE CA
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
HERE CERTIFICATE CRT
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
HERE CERTIFICATE PRIVATE
-----END RSA PRIVATE KEY-----
 
 
)KEY";

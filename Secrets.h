#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32_LDR2"                         //change this
 
const char WIFI_SSID[] = "alterwin";               //change this
const char WIFI_PASSWORD[] = "123456788";           //change this
const char AWS_IOT_ENDPOINT[] = "ac4v4pkzew2n-ats.iot.ap-southeast-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAOSQN1xqHyppNp/44UhMg2iVm8ZsMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA1MTAxNjA2
NTNaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDW7dYXBZTU2Oc/7Au5
04nKl9AfvBBXFLLB7COOHiKD3Phgrk/6HutVYIb8TFOLd8I+EBe+L7YysK9a1BN3
QFGUQkdB8GtVg0A75GNKxuY9o+KNpDdLmHR57C/F+ao3NAqZZYYNFdm5Xixh8KdZ
BhMsMcl6pNb2dpXfcdADnrUsAjHLQh5As2uudIbgZTLNvkQtNBrag9BEngpvQkBl
tgK+5Fo1cKSLNjOxVrB1Sy9X8BPAjdjUifAVNH4zSab7oKfI38fDsfiYTC+eLY7+
BnEBm4I6BMD+5kYhHN4zFuIpyx9/Rv6wBApPjGXGR3AXPn2te25SlU5GNEvhj4q7
9ptfAgMBAAGjYDBeMB8GA1UdIwQYMBaAFNuVHQEQsTfvFqKYL7BHJhBYMJOWMB0G
A1UdDgQWBBQvS1b3SRHrNshfCyQOgXLXgVtMgDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAHK7+XKNd5BGsBuM3Lswlz6O/
uI/YzbpF8iBLsYABbeyXuAFAnNtSL9aCC9A8QI9ZNMIJ2CyjyTQQwZtTw7yhWpl6
s1b17McLM7HtW9TjKShMcEoZxgEU+CvQ04fjJFgx3hNzK9RKqyPq08iDJy2y0xXl
9EG0h8EAUxo0M3oNyJ2bzn+T4x88iQfKhrdsrEXfWAaPrqsw6VkKFQ/cBLk2aPX4
ZypT9BZ5zGde539TYXBjVoAXXO8/7kg50lYROjaXu+8yKjdzTw3VbX9tQ/jgo3tr
Hys9XZXJrvJWZZ0QIHIoLhBX7GoBJKHKAFqiIROSIIQLQ4TIvFtC3IAoIbWWBQ==
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEA1u3WFwWU1NjnP+wLudOJypfQH7wQVxSywewjjh4ig9z4YK5P
+h7rVWCG/ExTi3fCPhAXvi+2MrCvWtQTd0BRlEJHQfBrVYNAO+RjSsbmPaPijaQ3
S5h0eewvxfmqNzQKmWWGDRXZuV4sYfCnWQYTLDHJeqTW9naV33HQA561LAIxy0Ie
QLNrrnSG4GUyzb5ELTQa2oPQRJ4Kb0JAZbYCvuRaNXCkizYzsVawdUsvV/ATwI3Y
1InwFTR+M0mm+6CnyN/Hw7H4mEwvni2O/gZxAZuCOgTA/uZGIRzeMxbiKcsff0b+
sAQKT4xlxkdwFz59rXtuUpVORjRL4Y+Ku/abXwIDAQABAoIBADmXZ2up0jSqnmSR
gp7boSuJPHqUcSh0YmX2OZzGVGdTGbcGXmXeTR8Gi4UliqlvgLwSodoTfNXeZE6J
T2H/+RwqGl//5TL3xYmG7FhILb/Mn1Nm8m4uPt/AuxhoiwTZzBFIlAADn+C87FWe
H6mKKC8KdDuJ2hQWuJg0LhIaP9+3hQibjKXtLm3YErM3nclO2wU9lSNN2lxeXJuh
qBZflOkvTSVfwQckxjBPwQCAq3n5t33LFn+oRzvPsisCiFxm/53LXOo8GgGRC85G
CgNJjCDktL0xf1OKzRcYZf7ic8C63winv9byByG5b51L9H1u4fQ334MmrJJeaSWx
65kDW4kCgYEA8wCHJ/UmUmKepGN4jhQapzPYeb7Y7l1Vtfj103rS8cwlPblMA+MN
NPkiS5BGr+hoOJPEYIE2T2Cn0K62TeLLxSZFv3tQAJBRpgbwgmbLaE/pb0Y6IrJk
uaVadSI/8xbvjAO5GWmLZPM0A4dRwITZ09evsac+pUFFjop4oZguKMUCgYEA4mzm
PV6MaJHYWuGm7rzOxevsSyFPKgB2XeiZUAnemeybL9WX+bp8vUdb7KdM1Tse7ufi
UiKvFxcF9w1oIlgJFoU6UaxMY+lSJPSy4IR1+vhTxp/oWXKRFFXG+NAbmbQjDeYi
q0Kf6tPNO/CCLL7SH0WnS+j0uxwRVvWFAyIFDdMCgYA2lk3GOhnLs/+zKe0w7W83
VDwyzR5qHWldoXmHcjXkv1k2TmO3E9ApsDV2CAj5Bxoya29Xxm7u0eWgyT6GrIXd
2cUdSJQmLEVLKI/qmzDiU+E6b+orVSuvUGfLnFAFSYeySjvQa5c2rDNo/4Lr3mwY
XIFJRSqbcNgxNwX2NvtXiQKBgBQg3i7ictTw8izSFobunesWWAEtyt3PALbEcKye
0/0W/Yy5DjOTEne5GkDldn0WLl/KmWH311zUHSGjPXigHt6zpUWRbZEMMtM6NZSj
8eEHplrn6D3bY25NWczQo0N8sgkQRlC3MYQso/gKH2he5ksFZCPpZ6gijKAQX2yx
34UlAoGABSQ/0N6VE0RVECCJ0ebYamW7Yejd5f7ozTv8RxXPFOdpq+kGOy2U5ZSk
TWY6+HtWT+tD94HmFdhYDwRLn0xJPfJmNgD6JlYr6nkRsuslZ0QVoq/Kj+nZx8XT
vWIA7LbPyg0/bngdv6S4igwwj1n+5NqCWB0SeN36MtkN53N9srs=
-----END RSA PRIVATE KEY-----
 
 
)KEY";
from OpenSSL import crypto
import PySimpleGUI as sg


def create_self_signed_cert(C, ST, L, O, OU, CN):
    KEY_FILE = "cert.key"
    CERT_FILE = "cert.crt"
    k = crypto.PKey()
    k.generate_key(crypto.TYPE_RSA, 1024)

    cert = crypto.X509()
    cert.get_subject().C = C
    cert.get_subject().ST = ST
    cert.get_subject().L = L
    cert.get_subject().O = O
    cert.get_subject().OU = OU
    cert.get_subject().CN = CN
    cert.set_serial_number(1000)
    cert.gmtime_adj_notBefore(0)
    cert.gmtime_adj_notAfter(10 * 365 * 24 * 60 * 60)
    cert.set_issuer(cert.get_subject())
    cert.set_pubkey(k)
    cert.sign(k, "sha1")
    open(CERT_FILE, "wt").write(crypto.dump_certificate(crypto.FILETYPE_PEM, cert).decode())
    open(KEY_FILE, "wt").write(crypto.dump_privatekey(crypto.FILETYPE_PEM, k).decode())


CA_CRT = "cert.crt"
CA_KEY = "cert.key"


def create_signed_cert(C, ST, L, O, OU, CN):
    KEY_FILE = "cert2.key"
    CERT_FILE = "cert2.crt"
    with open(CA_CRT, "rb") as certfile:
        ca_cert = crypto.load_certificate(crypto.FILETYPE_PEM, certfile.read())
    with open(CA_KEY, "rb") as key:
        ca_key = crypto.load_privatekey(crypto.FILETYPE_PEM, key.read())
    k = crypto.PKey()
    k.generate_key(crypto.TYPE_RSA, 1024)

    cert = crypto.X509()
    cert.get_subject().C = C
    cert.get_subject().ST = ST
    cert.get_subject().L = L
    cert.get_subject().O = O
    cert.get_subject().OU = OU
    cert.get_subject().CN = CN
    cert.set_serial_number(1000)
    cert.gmtime_adj_notBefore(0)
    cert.gmtime_adj_notAfter(10 * 365 * 24 * 60 * 60)
    cert.set_issuer(ca_cert.get_subject())
    cert.set_pubkey(k)
    cert.sign(k, "shal")
    open(CERT_FILE, "wt").write(crypto.dump_certificate(crypto.FILETYPE_PEM, cert).decode())
    open(KEY_FILE, "wt").write(crypto.dump_privatekey(crypto.FILETYPE_PEM, k).decode())


class Event:
    self_signed = "self signed"
    signed = "signed"
    close = "close"


window = sg.Window(
    "SSL cert",
    [
        [sg.Text("Country", size=(17, 1)), sg.InputText()],
        [sg.Text("State", size=(17, 1)), sg.InputText()],
        [sg.Text("City", size=(17, 1)), sg.InputText()],
        [sg.Text("Organization", size=(17, 1)), sg.InputText()],
        [sg.Text("Organizational Unit", size=(17, 1)), sg.InputText()],
        [sg.Text("name of the certificate", size=(17, 1)), sg.InputText()],
        [
            sg.Button(Event.self_signed),
            sg.Button(Event.signed),
            sg.Button(Event.close)
        ]
    ]
)
while True:
    event, values = window.read()
    if event == Event.close:
        break
    elif event == Event.self_signed:
        create_self_signed_cert(values[0], values[1], values[2], values[3], values[4], values[5])
        break
    elif event == Event.signed:
        create_signed_cert(values[0], values[1], values[2], values[3], values[4], values[5])
        break
window.close()

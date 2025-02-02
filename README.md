# Minecraft RCON Protocol Client
## Programda kullanılan RCON Protokolü

burada yaptığım RCON protokol implementasyonu minecraft
serverı üzerinde çalışmak üzerinedir fakat rcon.cpp/rcon.hpp dosyalarını
düzenleyip rcon kullanan diğer uygulamalara da portlayabilirsiniz.

[Minecraft WIKI](https://minecraft.wiki/w/RCON)

[Source RCON Protocol Valve](https://developer.valvesoftware.com/wiki/Source_RCON_Protocol) 

| Alan adı	 | Alan türü	 | Notlar| 
| ------     | ------      | -------|
| Length     | int32       |length boyutu dışında paketin geri kalan uzunluğu|
| Request ID | int32       |RCON Clientın soket iletişimi için üretmesi gereken ID değeri , RCON cevabı aynı ID üzerinden çevirir|
| Type       | int32       |RCON paketinin amacı 3=kimlik doğrulaması (login) , 2=server üzerinde komut çalıştırma|
| Payload	   | byte[]+1    |RCON paketinde verinin asıl taşındığı alandır burada gönderilecek komut veya RCON Password bulunur , null karakterle bitmelidir|
| Pad        | byte        |padding işlemleri paketi hizlama işlemleri için default 1byte |





## Kullanılan Çapraz Platform Kütüphaneler
| Kütüphane	 | Kullanım amacı|
| ------     | ------      
| wxWidgets  | tüm platformlarda GUI arayüzünü oluşturabilmek için kullanıldı |
| Boost::Asio| io işlemlerinin tüm platformlarda taşınabilir olması için kullanıldı |
| sqlite3    | cmake konfigurasyonu yapıldı fakat kullanılmadı |



## Eklenmesi ve düzeltilmesi gerekenler:
  + configParser.cpp sadece başarılı girişleri kaydediyor , otomatik olarak settings.cfg üzerinden okuma ile giriş yapılabilmeli
  + REMOTE CONTROL KONSOL penceresine ayarlar kısmı eklenmeli ve özelleştirmeye izin verilmeli
  + konsol kısmında servera veri göndermeden çalışacak bir konsol sistemi geliştirilmeli (# ile başlayan komutları işliyor fakat yetersiz #info)
  + çok uzun dönen yanıtlar düzgün bir biçimde ekranda gösterilmiyor


## Bağımlılıklar ve Build işlemi

### Bağımlılıkların kurulumu
```sh
sudo pacman -S boost boost-libs websocketpp wxwidgets-gtk3 wxwidgets-common #Arch
sudo apt-get install libboost-all-dev libwebsocketpp-dev libwxgtk3.0-gtk3-dev libwxbase3.0-dev #Ubuntu/Debian
```

### Build Linux
```sh
git clone https://github.com/why20w18/RCON-Protocol-Client.git && cd RCON-Protocol-Client
cr-UNIX.sh debug-compile
#cr-UNIX.sh compile #release olarak compile etmek icin
cr-UNIX.sh run
```

### Build Win32
```sh
git clone https://github.com/why20w18/RCON-Protocol-Client.git && cd RCON-Protocol-Client
cr-WIN32.sh compile
cr-WIN32.sh run
```

  
  


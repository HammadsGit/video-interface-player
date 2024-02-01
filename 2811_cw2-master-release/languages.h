#ifndef LANGUAGES_H
#define LANGUAGES_H
#include <QStringList>

// Holds translations of various UI strings.
class languages
{
public:
   languages(){};

   QStringList English = {"Media",
                          "Change Colour Theme",
                          "Audio On/Off",
                          "Effects",
                          "Transitions",
                          "Slow Mo",
                          "Size",
                          "Position",
                          "Rotation",
                          "Speed",
                          "Export",
                          "Opacity",
                          "Play/Pause",
                          "Skip Forward",
                          "Skip Backward",
                          "File",
                          "Open File",
                          "Open Folder",
                          "Settings",
                          "Language"
                         };
   QStringList Chinese = {"媒体",
                          "更改颜色主题",
                          "音频开/关",
                          "效果",
                          "过渡",
                          "慢动作",
                          "尺寸",
                          "位置",
                          "旋转",
                          "速度",
                          "导出",
                          "不透明度",
                          "播放/暂停",
                          "向前跳转",
                          "向后跳",
                          "档案",
                          "打开档案",
                          "打开目录",
                          "设置",
                          "语"
                         };
   QStringList Turkish = {"Medya",
                          "Renk Temasını Değiştir",
                          "Ses Açık/Kapalı",
                          "Etkileri",
                          "Geçişler",
                          "Ağır çekim",
                          "Boyut",
                          "Pozisyon",
                          "Döndürme",
                          "Hız",
                          "Aktarma Dosyası",
                          "Opaklık",
                          "Çal/Duraklat",
                          "İleri Atla",
                          "Geri Atla",
                          "Dosya",
                          "Dosya Aç",
                          "Klasörü Aç",
                          "Ayarlar",
                          "Dil"
                         };


};

#endif // LANGUAGES_H

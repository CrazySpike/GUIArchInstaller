#ifndef PAGES_H
#define PAGES_H

#pragma once
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QStringMatcher>
#include <QFile>

class Pages : public QWidget {
    Q_OBJECT

public:
    enum PageType { Locale, Keyboard, Zone, User, Installation };

    enum ZoneListMode { ZoneCategories, ZoneFiltered };

    explicit Pages(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;

    QWidget *createPage_Locale();
    QWidget *createPage_Keyboard();
    QWidget *createPage_Zone();
    QWidget *createPage_User();
    QWidget *createPage_Installation();

    // Add a WiFi Page

    void switchPage(PageType type);

    QVBoxLayout *zoneListLayout = nullptr;   // right-side list
    QWidget *zoneScrollWidget = nullptr;

    void populateZoneList(ZoneListMode type);

    QPushButton *createNavigationButtons(const QString &text, const QString &color);
    QPushButton *createFilterButtons(const QString &entry);
    QPushButton *createSelectionButtons(const QPair<QString, QString> &entry, PageType type);

    QVector<QPair<QString, QString>> filterZones(const QString &entry);

    void getLocale();

    void writeToEnv();

    QString fileName = "/Users/bwr/Desktop/Scripts/test.sh";

    // Default language, keyboard layout, timezone, and locale
    QString lang = "en";
    QString keyboard = "us";
    QString zone = "America/New_York";
    QString country = "US";
    QString locale = "en_US";

    QVector<QPair<QString, QString>> filteredZones;

    const QVector<QPair<QString, QString>> languages = {
        { "BahasaIndonesia", "id" },
        { "Bosanski", "bs" },
        { "Català", "ca" },
        { "Dansk", "da" },
        { "English", "en" },
        { "Esperanto", "eo" },
        { "Español", "es" },
        { "Français", "fr" },
        { "Hrvatski", "hr" },
        { "Italiano", "it" },
        { "Latviešu", "lv" },
        { "Lietuvių", "lt" },
        { "Magyar", "hu" },
        { "Nederlands", "nl" },
        { "NorskBokmål", "nb" },
        { "Polski", "pl" },
        { "Português", "pt" },
        { "Qhichwa", "qu" },
        { "Română", "ro" },
        { "Slovenčina", "sk" },
        { "Slovenščina", "sl" },
        { "Suomi", "fi" },
        { "Svenska", "sv" },
        { "Türkçe", "tr" },
        { "粵語", "yue" },
        { "文言文", "zh" },
        { "正體中文", "zh" },
        { "Čeština", "cs" },
        { "Ελληνικά", "el" },
        { "Български", "bg" },
        { "Русский", "ru" },
        { "Српски", "sr" },
        { "Українська", "uk" },
        { "العربية", "ar" },
        { "עברית", "he" },
        { "فارسی", "fa" },
        { "हिन्दी", "hi" },
        { "বাংলা", "bn" },
        { "ไทย", "th" },
        { "한국어", "ko" }
    };

    const QVector<QString> timeZoneCategories = {
        {"Africa"},
        {"America"},
        {"Antarctica"},
        {"Asia"},
        {"Atlantic"},
        {"Australia"},
        {"Europe"},
        {"Indian"},
        {"Pacific"}
    };

    const QVector<QPair<QString, QString>> timeZones = {
        { "Africa/Abidjan", "CI" },
        { "Africa/Algiers", "DZ" },
        { "Africa/Bissau", "GW" },
        { "Africa/Cairo", "EG" },
        { "Africa/Casablanca", "MA" },
        { "Africa/El_Aaiun", "EH" },
        { "Africa/Johannesburg", "ZA" },
        { "Africa/Juba", "SS" },
        { "Africa/Khartoum", "SD" },
        { "Africa/Lagos", "NG" },
        { "Africa/Maputo", "MZ" },
        { "Africa/Monrovia", "LR" },
        { "Africa/Nairobi", "KE" },
        { "Africa/Ndjamena", "TD" },
        { "Africa/Sao_Tome", "ST" },
        { "Africa/Tripoli", "LY" },
        { "Africa/Tunis", "TN" },
        { "Africa/Windhoek", "NA" },
        { "Africa/Ceuta", "ES" },

        { "America/Araguaina", "BR" },
        { "America/Argentina/Buenos_Aires", "AR" },
        { "America/Argentina/Catamarca", "AR" },
        { "America/Argentina/Cordoba", "AR" },
        { "America/Argentina/Jujuy", "AR" },
        { "America/Argentina/La_Rioja", "AR" },
        { "America/Argentina/Mendoza", "AR" },
        { "America/Argentina/Rio_Gallegos", "AR" },
        { "America/Argentina/Salta", "AR" },
        { "America/Argentina/San_Juan", "AR" },
        { "America/Argentina/San_Luis", "AR" },
        { "America/Argentina/Tucuman", "AR" },
        { "America/Argentina/Ushuaia", "AR" },
        { "America/Asuncion", "PY" },
        { "America/Bahia", "BR" },
        { "America/Belem", "BR" },
        { "America/Boa_Vista", "BR" },
        { "America/Bogota", "CO" },
        { "America/Campo_Grande", "BR" },
        { "America/Caracas", "VE" },
        { "America/Cayenne", "GF" },
        { "America/Coyhaique", "CL" },
        { "America/Cuiaba", "BR" },
        { "America/Eirunepe", "BR" },
        { "America/Fortaleza", "BR" },
        { "America/Guayaquil", "EC" },
        { "America/Guyana", "GY" },
        { "America/La_Paz", "BO" },
        { "America/Lima", "PE" },
        { "America/Maceio", "BR" },
        { "America/Manaus", "BR" },
        { "America/Montevideo", "UY" },
        { "America/Noronha", "BR" },
        { "America/Paramaribo", "SR" },
        { "America/Porto_Velho", "BR" },
        { "America/Punta_Arenas", "CL" },
        { "America/Recife", "BR" },
        { "America/Rio_Branco", "BR" },
        { "America/Santarem", "BR" },
        { "America/Santiago", "CL" },
        { "America/Sao_Paulo", "BR" },
        { "America/Danmarkshavn", "GL" },
        { "America/Nuuk", "GL" },
        { "America/Scoresbysund", "GL" },
        { "America/Thule", "GL" },
        { "America/Adak", "US" },
        { "America/Anchorage", "US" },
        { "America/Bahia_Banderas", "MX" },
        { "America/Barbados", "BB" },
        { "America/Belize", "BZ" },
        { "America/Boise", "US" },
        { "America/Cambridge_Bay", "CA" },
        { "America/Cancun", "MX" },
        { "America/Chicago", "US" },
        { "America/Chihuahua", "MX" },
        { "America/Ciudad_Juarez", "MX" },
        { "America/Costa_Rica", "CR" },
        { "America/Dawson", "CA" },
        { "America/Dawson_Creek", "CA" },
        { "America/Denver", "US" },
        { "America/Detroit", "US" },
        { "America/Edmonton", "CA" },
        { "America/El_Salvador", "SV" },
        { "America/Fort_Nelson", "CA" },
        { "America/Glace_Bay", "CA" },
        { "America/Goose_Bay", "CA" },
        { "America/Grand_Turk", "TC" },
        { "America/Guatemala", "GT" },
        { "America/Halifax", "CA" },
        { "America/Havana", "CU" },
        { "America/Hermosillo", "MX" },
        { "America/Indiana/Indianapolis", "US" },
        { "America/Indiana/Knox", "US" },
        { "America/Indiana/Marengo", "US" },
        { "America/Indiana/Petersburg", "US" },
        { "America/Indiana/Tell_City", "US" },
        { "America/Indiana/Vevay", "US" },
        { "America/Indiana/Vincennes", "US" },
        { "America/Indiana/Winamac", "US" },
        { "America/Inuvik", "CA" },
        { "America/Iqaluit", "CA" },
        { "America/Jamaica", "JM" },
        { "America/Juneau", "US" },
        { "America/Kentucky/Louisville", "US" },
        { "America/Kentucky/Monticello", "US" },
        { "America/Los_Angeles", "US" },
        { "America/Managua", "NI" },
        { "America/Martinique", "MQ" },
        { "America/Matamoros", "MX" },
        { "America/Mazatlan", "MX" },
        { "America/Menominee", "US" },
        { "America/Merida", "MX" },
        { "America/Metlakatla", "US" },
        { "America/Mexico_City", "MX" },
        { "America/Miquelon", "PM" },
        { "America/Moncton", "CA" },
        { "America/Monterrey", "MX" },
        { "America/New_York", "US" },
        { "America/Nome", "US" },
        { "America/North_Dakota/Beulah", "US" },
        { "America/North_Dakota/Center", "US" },
        { "America/North_Dakota/New_Salem", "US" },
        { "America/Ojinaga", "MX" },
        { "America/Panama", "PA" },
        { "America/Phoenix", "US" },
        { "America/Port-au-Prince", "HT" },
        { "America/Puerto_Rico", "PR" },
        { "America/Rankin_Inlet", "CA" },
        { "America/Regina", "CA" },
        { "America/Resolute", "CA" },
        { "America/Santo_Domingo", "DO" },
        { "America/Sitka", "US" },
        { "America/St_Johns", "CA" },
        { "America/Swift_Current", "CA" },
        { "America/Tegucigalpa", "HN" },
        { "America/Tijuana", "MX" },
        { "America/Toronto", "CA" },
        { "America/Vancouver", "CA" },
        { "America/Whitehorse", "CA" },
        { "America/Winnipeg", "CA" },
        { "America/Yakutat", "US" },

        { "Antarctica/Casey", "AQ" },
        { "Antarctica/Davis", "AQ" },
        { "Antarctica/Mawson", "AQ" },
        { "Antarctica/Rothera", "AQ" },
        { "Antarctica/Troll", "AQ" },
        { "Antarctica/Vostok", "AQ" },
        { "Antarctica/Macquarie", "AU" },
        { "Antarctica/Palmer", "AQ" },

        { "Asia/Almaty", "KZ" },
        { "Asia/Amman", "JO" },
        { "Asia/Aqtau", "KZ" },
        { "Asia/Aqtobe", "KZ" },
        { "Asia/Ashgabat", "TM" },
        { "Asia/Atyrau", "KZ" },
        { "Asia/Baghdad", "IQ" },
        { "Asia/Baku", "AZ" },
        { "Asia/Bangkok", "TH" },
        { "Asia/Beirut", "LB" },
        { "Asia/Bishkek", "KG" },
        { "Asia/Colombo", "LK" },
        { "Asia/Damascus", "SY" },
        { "Asia/Dhaka", "BD" },
        { "Asia/Dili", "TL" },
        { "Asia/Dubai", "AE" },
        { "Asia/Dushanbe", "TJ" },
        { "Asia/Famagusta", "CY" },
        { "Asia/Gaza", "PS" },
        { "Asia/Hebron", "PS" },
        { "Asia/Ho_Chi_Minh", "VN" },
        { "Asia/Hong_Kong", "HK" },
        { "Asia/Hovd", "MN" },
        { "Asia/Jakarta", "ID" },
        { "Asia/Jayapura", "ID" },
        { "Asia/Jerusalem", "IL" },
        { "Asia/Kabul", "AF" },
        { "Asia/Karachi", "PK" },
        { "Asia/Kathmandu", "NP" },
        { "Asia/Kolkata", "IN" },
        { "Asia/Kuching", "MY" },
        { "Asia/Macau", "MO" },
        { "Asia/Makassar", "ID" },
        { "Asia/Manila", "PH" },
        { "Asia/Nicosia", "CY" },
        { "Asia/Oral", "KZ" },
        { "Asia/Pontianak", "ID" },
        { "Asia/Pyongyang", "KP" },
        { "Asia/Qatar", "QA" },
        { "Asia/Qostanay", "KZ" },
        { "Asia/Qyzylorda", "KZ" },
        { "Asia/Riyadh", "SA" },
        { "Asia/Samarkand", "UZ" },
        { "Asia/Seoul", "KR" },
        { "Asia/Shanghai", "CN" },
        { "Asia/Singapore", "SG" },
        { "Asia/Taipei", "TW" },
        { "Asia/Tashkent", "UZ" },
        { "Asia/Tbilisi", "GE" },
        { "Asia/Tehran", "IR" },
        { "Asia/Thimphu", "BT" },
        { "Asia/Tokyo", "JP" },
        { "Asia/Ulaanbaatar", "MN" },
        { "Asia/Urumqi", "CN" },
        { "Asia/Yangon", "MM" },
        { "Asia/Yerevan", "AM" },
        { "Asia/Anadyr", "RU" },
        { "Asia/Barnaul", "RU" },
        { "Asia/Chita", "RU" },
        { "Asia/Irkutsk", "RU" },
        { "Asia/Kamchatka", "RU" },
        { "Asia/Khandyga", "RU" },
        { "Asia/Krasnoyarsk", "RU" },
        { "Asia/Magadan", "RU" },
        { "Asia/Novokuznetsk", "RU" },
        { "Asia/Novosibirsk", "RU" },
        { "Asia/Omsk", "RU" },
        { "Asia/Sakhalin", "RU" },
        { "Asia/Srednekolymsk", "RU" },
        { "Asia/Tomsk", "RU" },
        { "Asia/Ust-Nera", "RU" },
        { "Asia/Vladivostok", "RU" },
        { "Asia/Yakutsk", "RU" },
        { "Asia/Yekaterinburg", "RU" },

        { "Atlantic/Cape_Verde", "CV" },
        { "Atlantic/South_Georgia", "GS" },
        { "Atlantic/Stanley", "FK" },
        { "Atlantic/Azores", "PT" },
        { "Atlantic/Canary", "ES" },
        { "Atlantic/Faroe", "FO" },
        { "Atlantic/Madeira", "PT" },
        { "Atlantic/Bermuda", "BM" },

        { "Australia/Adelaide", "AU" },
        { "Australia/Brisbane", "AU" },
        { "Australia/Broken_Hill", "AU" },
        { "Australia/Darwin", "AU" },
        { "Australia/Eucla", "AU" },
        { "Australia/Hobart", "AU" },
        { "Australia/Lindeman", "AU" },
        { "Australia/Lord_Howe", "AU" },
        { "Australia/Melbourne", "AU" },
        { "Australia/Perth", "AU" },
        { "Australia/Sydney", "AU" },

        { "Europe/Andorra", "AD" },
        { "Europe/Astrakhan", "RU" },
        { "Europe/Athens", "GR" },
        { "Europe/Belgrade", "RS" },
        { "Europe/Berlin", "DE" },
        { "Europe/Brussels", "BE" },
        { "Europe/Bucharest", "RO" },
        { "Europe/Budapest", "HU" },
        { "Europe/Chisinau", "MD" },
        { "Europe/Dublin", "IE" },
        { "Europe/Gibraltar", "GI" },
        { "Europe/Helsinki", "FI" },
        { "Europe/Istanbul", "TR" },
        { "Europe/Kaliningrad", "RU" },
        { "Europe/Kirov", "RU" },
        { "Europe/Kyiv", "UA" },
        { "Europe/Lisbon", "PT" },
        { "Europe/London", "GB" },
        { "Europe/Madrid", "ES" },
        { "Europe/Malta", "MT" },
        { "Europe/Minsk", "BY" },
        { "Europe/Moscow", "RU" },
        { "Europe/Paris", "FR" },
        { "Europe/Prague", "CZ" },
        { "Europe/Riga", "LV" },
        { "Europe/Rome", "IT" },
        { "Europe/Samara", "RU" },
        { "Europe/Saratov", "RU" },
        { "Europe/Simferopol", "UA" },
        { "Europe/Sofia", "BG" },
        { "Europe/Tallinn", "EE" },
        { "Europe/Tirane", "AL" },
        { "Europe/Ulyanovsk", "RU" },
        { "Europe/Vienna", "AT" },
        { "Europe/Vilnius", "LT" },
        { "Europe/Volgograd", "RU" },
        { "Europe/Warsaw", "PL" },
        { "Europe/Zurich", "CH" },

        { "Indian/Mauritius", "MU" },
        { "Indian/Chagos", "IO" },
        { "Indian/Maldives", "MV" },

        { "Pacific/Apia", "WS" },
        { "Pacific/Auckland", "NZ" },
        { "Pacific/Bougainville", "PG" },
        { "Pacific/Chatham", "NZ" },
        { "Pacific/Efate", "VU" },
        { "Pacific/Fakaofo", "TK" },
        { "Pacific/Fiji", "FJ" },
        { "Pacific/Gambier", "PF" },
        { "Pacific/Guadalcanal", "SB" },
        { "Pacific/Guam", "GU" },
        { "Pacific/Kanton", "KI" },
        { "Pacific/Kiritimati", "KI" },
        { "Pacific/Kosrae", "FM" },
        { "Pacific/Kwajalein", "MH" },
        { "Pacific/Marquesas", "PF" },
        { "Pacific/Nauru", "NR" },
        { "Pacific/Niue", "NU" },
        { "Pacific/Norfolk", "NF" },
        { "Pacific/Noumea", "NC" },
        { "Pacific/Pago_Pago", "AS" },
        { "Pacific/Palau", "PW" },
        { "Pacific/Pitcairn", "PN" },
        { "Pacific/Port_Moresby", "PG" },
        { "Pacific/Rarotonga", "CK" },
        { "Pacific/Tahiti", "PF" },
        { "Pacific/Tarawa", "KI" },
        { "Pacific/Tongatapu", "TO" },
        { "Pacific/Easter", "CL" },
        { "Pacific/Galapagos", "EC" },
        { "Pacific/Honolulu", "US" }
    };

    const QStringList localeCodes = {
        // Bahasa Indonesia
        "id_ID",

        // Bosnian
        "bs_BA",

        // Catalan
        "ca_AD",
        "ca_ES",
        "ca_FR",
        "ca_IT",

        // Danish
        "da_DK",

        // English
        "en_US",
        "en_AG",
        "en_AU",
        "en_BW",
        "en_CA",
        "en_DK",
        "en_GB",
        "en_HK",
        "en_IE",
        "en_IL",
        "en_IN",
        "en_NG",
        "en_NZ",
        "en_PH",
        "en_SC",
        "en_SG",
        "en_ZA",
        "en_ZM",
        "en_ZW",

        // Esperanto
        "eo",

        // Spanish
        "es_AR",
        "es_BO",
        "es_CL",
        "es_CO",
        "es_CR",
        "es_CU",
        "es_DO",
        "es_EC",
        "es_ES",
        "es_GT",
        "es_HN",
        "es_MX",
        "es_NI",
        "es_PA",
        "es_PE",
        "es_PR",
        "es_PY",
        "es_SV",
        "es_US",
        "es_UY",
        "es_VE",

        // French
        "fr_FR",
        "fr_BE",
        "fr_CA",
        "fr_CH",
        "fr_LU",

        // Croatian
        "hr_HR",

        // Italian
        "it_IT",
        "it_CH",

        // Latvian
        "lv_LV",

        // Lithuanian
        "lt_LT",

        // Hungarian
        "hu_HU",

        // Dutch
        "nl_NL",
        "nl_AW",
        "nl_BE",

        // Norwegian Bokmål
        "nb_NO",

        // Polish
        "pl_PL",

        // Portuguese
        "pt_PT",
        "pt_BR",

        // Quechua
        "qu_BO",
        "qu_EC",
        "qu_PE",

        // Romanian
        "ro_RO",

        // Slovak
        "sk_SK",

        // Slovenian
        "sl_SI",

        // Finnish
        "fi_FI",

        // Swedish
        "sv_SE",
        "sv_FI",

        // Turkish
        "tr_TR",
        "tr_CY",

        // Cantonese
        "yue_HK",

        // Simplified Chinese
        "zh_CN",
        "zh_SG",

        // Traditional Chinese
        "zh_HK",
        "zh_TW",
        "zh_MO",

        // Czech
        "cs_CZ",

        // Greek
        "el_GR",
        "el_CY",

        // Bulgarian
        "bg_BG",

        // Russian
        "ru_RU",
        "ru_UA",

        // Serbian
        "sr_ME",
        "sr_RS",

        // Ukrainian
        "uk_UA",

        // Hebrew
        "he_IL",

        // Arabic
        "ar_AE",
        "ar_BH",
        "ar_DZ",
        "ar_EG",
        "ar_IN",
        "ar_IQ",
        "ar_JO",
        "ar_KW",
        "ar_LB",
        "ar_LY",
        "ar_MA",
        "ar_OM",
        "ar_QA",
        "ar_SA",
        "ar_SD",
        "ar_SS",
        "ar_SY",
        "ar_TN",
        "ar_YE",

        // Persian
        "fa_IR",

        // Hindi
        "hi_IN",

        // Bengali
        "bn_BD",
        "bn_IN",

        // Thai
        "th_TH",

        // Korean
        "ko_KR"
    };

    const QVector<QPair<QString, QString>> keyboardLayouts = {
        {"Afghanistan", "af"},
        {"Albania", "al"},
        {"Armenia", "am"},
        {"Arabic", "ara"},
        {"Austria", "at"},
        {"Australia", "au"},
        {"Azerbaijan", "az"},

        {"Bosnia and Herzegovina", "ba"},
        {"Bangladesh", "bd"},
        {"Belgium", "be"},
        {"Bulgaria", "bg"},
        {"Brazil", "br"},
        {"Braille", "brai"},
        {"Bhutan", "bt"},
        {"Botswana", "bw"},
        {"Belarus", "by"},

        {"Canada", "ca"},
        {"Democratic Republic of the Congo", "cd"},
        {"Switzerland", "ch"},
        {"Cameroon", "cm"},
        {"China", "cn"},
        {"Czech Republic", "cz"},

        {"Germany", "de"},
        {"Denmark", "dk"},
        {"Algeria", "dz"},

        {"Estonia", "ee"},
        {"Egypt", "eg"},
        {"Esperanto", "epo"},
        {"Spain", "es"},
        {"Ethiopia", "et"},

        {"Finland", "fi"},
        {"Faroe Islands", "fo"},
        {"France", "fr"},

        {"United Kingdom", "gb"},
        {"Georgia", "ge"},
        {"Ghana", "gh"},
        {"Guinea", "gn"},
        {"Greece", "gr"},

        {"Croatia", "hr"},
        {"Hungary", "hu"},

        {"Indonesia", "id"},
        {"Ireland", "ie"},
        {"Israel", "il"},
        {"India", "in"},
        {"Iraq", "iq"},
        {"Iran", "ir"},
        {"Iceland", "is"},
        {"Italy", "it"},

        {"Japan", "jp"},

        {"Kenya", "ke"},
        {"Kyrgyzstan", "kg"},
        {"Cambodia", "kh"},
        {"South Korea", "kr"},
        {"Kazakhstan", "kz"},

        {"Laos", "la"},
        {"Latin America", "latam"},
        {"Sri Lanka", "lk"},
        {"Lithuania", "lt"},
        {"Latvia", "lv"},

        {"Morocco", "ma"},
        {"Moldova", "md"},
        {"Montenegro", "me"},
        {"North Macedonia", "mk"},
        {"Mali", "ml"},
        {"Myanmar", "mm"},
        {"Mongolia", "mn"},
        {"Malta", "mt"},
        {"Maldives", "mv"},
        {"Malaysia", "my"},

        {"Nigeria", "ng"},
        {"Netherlands", "nl"},
        {"Norway", "no"},
        {"Nepal", "np"},
        {"New Zealand", "nz"},

        {"Philippines", "ph"},
        {"Pakistan", "pk"},
        {"Poland", "pl"},
        {"Portugal", "pt"},

        {"Romania", "ro"},
        {"Serbia", "rs"},
        {"Russia", "ru"},

        {"Sweden", "se"},
        {"Slovenia", "si"},
        {"Slovakia", "sk"},
        {"Senegal", "sn"},
        {"Syria", "sy"},

        {"Togo", "tg"},
        {"Thailand", "th"},
        {"Tajikistan", "tj"},
        {"Turkmenistan", "tm"},
        {"Turkey", "tr"},
        {"Taiwan", "tw"},
        {"Tanzania", "tz"},

        {"Ukraine", "ua"},
        {"United States", "us"},
        {"Uzbekistan", "uz"},

        {"Vietnam", "vn"},
        {"South Africa", "za"}
    };


};

#endif // PAGES_H

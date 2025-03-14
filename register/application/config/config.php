<?php
/**
 * @author Amin Mahmoudi (MasterkinG)
 * @copyright    Copyright (c) 2019 - 2021, MasterkinG32. (https://masterking32.com)
 * @link    https://masterking32.com
 * @Description : It's not masterking32 framework !
 **/

/*===================================================================
baseurl
    That's your website URL. Example: "https://DOMAIN.COM"
page_title
    That's your website title. Example: "My WOW Private server!"
language
    Default website language (english/persian/italian/chinese-simplified/chinese-traditional/swedish/french/german/spanish/korean/russian)
supported_langs
	List of languages supported, You can remove each language you don't want!
	if you want to disable language changer, Change it to: $config['supported_langs'] = false;
=====================================================================*/
$config['baseurl'] = "http://localhost"; // MAKE SURE USE VALID URL, If you have any issue loading images and template please check this field
$config['page_title'] = "Simple Register";
$config['language'] = "chinese-simplified";
$config['supported_langs'] = [
	'english' => 'English',
	'persian' => 'Persian',
	'italian' => 'Italian',
	'chinese-simplified' => 'Chinese Simplified',
	'chinese-traditional' => 'Chinese Traditional',
	'swedish' => 'Swedish',
	'french' => 'French',
	'german' => 'German',
	'spanish' => 'Spanish',
	'korean' => 'Korean',
	'russian' => 'Russian'
];
/*===================================================================
If you see a white screen or have an issue, you can enable it to see the errors.
Note that after testing, be sure to disable this option.
=====================================================================*/
$config['debug_mode'] = false; // ENABLE Debug mode if you got blank screen or 503 error, to see what happen?
/*===================================================================
Your server information.
realmlist
    Server Realmlist
patch_location
    If have patch set URL to download our patch here or make that empty
game_version
    Your game version
=====================================================================*/
$config['realmlist'] = '124.71.152.254';
$config['patch_location'] = '';
$config['game_version'] = '3.3.5a (12340)';
/*===================================================================
Select your server expansion.
If you want to use advance template, Your images and backgrounds will be changed for your expansion.
0 = Classic
1 = The Burning Crusade (TBC)
2 = Wrath of the Lich King (WotLK)
3 = Cataclysm
4 = Mist of Pandaria (MOP)
5 = Warlords of Draenor (WOD)
6 = Legion
7 = BFA (I'm not sure about this one!)
=====================================================================*/
$config['expansion'] = '2';
/*===================================================================
Core Type:
0 = TrinityCore
1 = AzerothCore
2 = AshamaneCore
3 = Skyfire Project
4 = OregonCore
5 = CMangos
10 = etc
=====================================================================*/
$config['server_core'] = 0;
/*===================================================================
If your server is WoD/Legion/BFA you should enable it!
=====================================================================*/
$config['battlenet_support'] = false;
/*===================================================================
If your core password encryption is SRP6, you need to enable it.
For the last versions of the TrinityCore(3.3.5/master)/AzerothCore, you need to enable it. https://git.io/JJRH4 and https://git.io/JJrxq
Enable that if you use the last version of TC.
For old versions, Make sure this feature is disabled.
You need to enable the GMP extension for PHP.
=====================================================================
***************** GMP REQUIRED ********************
******Uncomment extension=gmp in your php.ini******
=====================================================================*/
$config['srp6_support'] = false; // READ COMMENTS, [Please ENABLE GMP]
/*===================================================================
If you have an issue with top players or online players you can disable them!
disable_top_players
    Disable server top players page [true: Hide top players page]
disable_online_players
    Disable online players page [true: Hide online players page]
disable_changepassword
    Disable change password
    Change this to true, If you are using SOAP for registration.
=====================================================================*/
$config['disable_top_players'] = false;
$config['disable_online_players'] = false;
$config['disable_changepassword'] = false;
/*===================================================================
Allow to users make account with an email for several accounts (Just work for non-battle.net servers)
=====================================================================*/
$config['multiple_email_use'] = true;
/*===================================================================
Template name, You can change it to:
light
advance
icecrown
kaelthas
battleforazeroth
=====================================================================*/
$config['template'] = 'light';
/*===================================================================
SMTP config.
We need this part to send an email. (used for restore password and 2FA)
You can use your own SMTP or Gmail/Yahoo/Hotmail and etc
smtp_host
    Specify main and backup SMTP servers
smtp_port
    TCP port to connect to
smtp_auth
    Enable SMTP authentication
smtp_user
    SMTP username
smtp_pass
    SMTP password
smtp_secure
    Enable TLS encryption, `ssl` also accepted
smtp_mail
    Send emails by ...
=====================================================================*/
$config['smtp_host'] = 'smtp.sina.com';
$config['smtp_port'] = 25;
$config['smtp_auth'] = false;
$config['smtp_user'] = 'lyf_liyunfan@sina.com';
#$config['smtp_pass'] = '1463fb7b303ef2bf';
$config['smtp_pass'] = 'l1i2y2u3nfan';
$config['smtp_secure'] = 'ssl';
$config['smtp_mail'] = 'lyf_liyunfan@sina.com';
/*===================================================================
vote_system
    You can enable/disable vote system.
    Vote system is a simple and don't have postback or something like that to verify the votes
    If you use Cloudflare and you have issue with IPs and voting, Read this: https://support.cloudflare.com/hc/en-us/articles/200170786
vote_sites
    Your vote sites and images, must be array.
=====================================================================*/
$config['vote_system'] = false;
$config['vote_sites'] = array(
    array(
        'image' => 'http://www.top100arena.com/hit.asp?id=93137&c=WoW&t=2',
        'site_url' => 'http://www.top100arena.com/in.asp?id=93137'
    ),
    array(
        'image' => 'https://topg.org/topg.gif',
        'site_url' => 'https://topg.org/wow-private-servers/in-479394'
    ),
    array(
        'image' => 'http://www.xtremeTop100.com/votenew.jpg',
        'site_url' => 'http://www.xtremetop100.com/in.php?site=1132364316'
    )
);
/*===================================================================
You can use Image captcha or HCaptcha or Recaptcha v2.
If you want to use Recaptcha v2 or HCaptcha required to enable cURL in your PHP.
** We recommend using HCaptcha. **
captcha_type
    0) Image Captcha
    1) HCaptcha
    2) ReCaptcha v2
    +2) Disable captcha. (DON'T DO THAT!)
For image captcha, you don't need to put anything for captcha_key captcha_secret or captcha_language.
captcha_secret/captcha_secret
    To get key and secret for HCaptcha go to https://hCaptcha.com/?r=6d4f9117ba12
    To get key and secret for Recaptcha go to https://www.google.com/recaptcha
captcha_language
    https://docs.hcaptcha.com/languages
    https://developers.google.com/recaptcha/docs/language
=====================================================================
******Uncomment extension=gd2 in your php.ini******
=====================================================================*/
$config['captcha_type'] = 0;
$config['captcha_key'] = '';
$config['captcha_secret'] = '';
$config['captcha_language'] = 'en';
/*===================================================================
soap_for_register
    Don't Enable it for AzerothCore/TrinityCore/SkyFire and AshamaneCore.
    If you enable that you need to disabled change password feature.
    If you want to enable Two-Factor Authentication (2FA) you don't need to enable this option.
    For Two-Factor Authentication (2FA)  just need to config other parts of the SOAP.

SOAP features need to enable soap in your PHP.

soap_host
    SOAP server address
soap_port
    SOAP server port.
soap_uri
    urn:TC for TrinityCore
    urn:AC for AzerothCore
    urn:MaNGOS for Mangos
soap_style
    SOAP style
soap_username
    SOAP account username
soap_password
    SOAP account password
soap_ca_command
    Create account command
    You can use it like this too: '.account create {USERNAME} {PASSWORD} {PASSWORD} {EMAIL}'
    Check create account command in your server!
soap_cp_command
    Change password command
    account set password {USERNAME} {PASSWORD} {PASSWORD}
    Check change password command in your server
soap_asa_command
    If you use soap_for_register, You need to set this command.
    This command will be run after soap_ca_command.
    If you don't want to run any command after soap_ca_command you can make it empty like this: ''
    account set addon {USERNAME} {EXPANSION}
=====================================================================
******Uncomment extension=soap in your php.ini******
=====================================================================*/
$config['soap_for_register'] = false;
$config['soap_host'] = '127.0.0.1';
$config['soap_port'] = '7878';
$config['soap_uri'] = 'urn:TC';
$config['soap_style'] = 'SOAP_RPC';
$config['soap_username'] = 'test';
$config['soap_password'] = 'test';
$config['soap_ca_command'] = 'account create {USERNAME} {PASSWORD}';
$config['soap_cp_command'] = 'account set password {USERNAME} {PASSWORD} {PASSWORD}';
$config['soap_asa_command'] = 'account set addon {USERNAME} {EXPANSION}';
/*===================================================================
Two-Factor Authentication (2FA)
Your core must support 2fa.
This feature just works for cores that have 2fa command.
If your core support 2fa but don't have any command, you can check this: https://github.com/masterking32/WoWSimpleRegistration/pull/20 (Support some of the cores, Required to use 2fa for registration.)

You need to config SOAP too but you don't need to enable 'soap_for_register'.
For security reasons, We used email to enable 2fa, You need to enable SMTP config.

2fa_support
    You can enable or disable it. (true/false)
soap_2d_command
    Command to disable 2fa.
    account set 2fa {USERNAME} off
soap_2e_command
    Command to enable 2fa.
    account set 2fa {USERNAME} {SECRET}
=====================================================================*/
$config['2fa_support'] = false;
$config['soap_2d_command'] = 'account set 2fa {USERNAME} off';
$config['soap_2e_command'] = 'account set 2fa {USERNAME} {SECRET}';
/*===================================================================
You Auth/Realmd MySQL information.
db_auth_host
    Auth Database Host
db_auth_port
    Auth Database Port
db_auth_user
    Auth Database Username
db_auth_pass
    Auth Database Password
db_auth_dbname
    Auth Database DBName
=====================================================================*/
$config['db_auth_host'] = 'mysql';
$config['db_auth_port'] = '3306';
$config['db_auth_user'] = 'root';
$config['db_auth_pass'] = 'root';
$config['db_auth_dbname'] = 'auth';
/*===================================================================
Your character's databases.
If your server has a lot of realms you can check the example at the bottom of the file.
=====================================================================*/
$config['realmlists'] = array(
    "1" => array(
        'realmid' => 1, // Realm ID
        'realmname' => "TrinityCore", // Realm Name
        'db_host' => "mysql", // MySQL Host IP
        'db_port' => "3306", // MySQL Host Port
        'db_user' => "root", // MySQL username
        'db_pass' => 'root', // MySQL password
        'db_name' => "characters" // Characters database name
    )
);

/*
 **********************************
 * EXMAPLE OF MORE THAN ONE REALM *
 **********************************

$config['realmlists'] = array( // Add your realmlist here
    "1" => array(
        'realmid' => 1,
        'realmname' => "Realm 1",
        'db_host' => "127.0.0.1",
        'db_port' => "3306",
        'db_user' => "root",
        'db_pass' => "root",
        'db_name' => "rm1_chars"
    ),
    "2" => array(
        'realmid' => 2,
        'realmname' => "Realm 2",
        'db_host' => "127.0.0.1",
        'db_port' => "3306",
        'db_user' => "root",
        'db_pass' => "root",
        'db_name' => "rm2_chars"
    ),
    "3" => array(
        'realmid' => 3,
        'realmname' => "Realm 3",
        'db_host' => "127.0.0.1",
        'db_port' => "3306",
        'db_user' => "root",
        'db_pass' => "root",
        'db_name' => "rm3_chars"
    )
);
*/



$config['script_version'] = '2.0.2';

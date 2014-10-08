<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

$domain = explode( '.', $_SERVER["HTTP_HOST"] );
$file = '/dns/' . array_pop( $domain ) . '/' . array_pop( $domain ) . '/etc/settings' . '/' . implode( '.', $domain ) . '.ini';
if( file_exists( $file ) )
{
    $conf = parse_ini_file( $file, true );
    $conf['type'] = 'file';
}
else if( file_exists( '../www.ini' ) )
{
    $conf = parse_ini_file('../www.ini', true);
    $conf['type'] = 'file';
}

$GLOBALS['CONFIG']['API_HOST'] 		 = 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	 = $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	 = $conf['Main']['API_TOKEN'];
$GLOBALS['CONFIG']['HOSTNAME']		 = $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['UPTIME_TOKEN']	 = $conf['Main']['UPTIME_TOKEN'];
$GLOBALS['CONFIG']['DOMAIN_GENERIC'] = $conf['Main']['DOMAIN_GENERIC'];
$GLOBALS['CONFIG']['REDMINE_TOKEN']	 = $conf['Main']['REDMINE_TOKEN'];
$GLOBALS['CONFIG']['DEBUG'] 		 = false;
unset($conf);
unset($file);
unset($domain);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/?elogin';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'FR';

$GLOBALS['CONFIG']['MAIL_TEMPLATE'] = "
<html>
<head>
	<title>Another Service</title>
</head>
<body style=\"background-color: #e5e9ee; margin: 0; font-family: Arial; font-size: 15px; font-weight: normal; line-height: 18px; color: #404040;\">
	<div style=\"background-color: #11193e; width: 100%; height: 60px; padding: 20px 10px 10px 10px; margin-bottom: 20px; text-align: center;\">
		<img src=\"https://www.anotherservice.com/as/images/logo.png\" alt=\"\" />
	</div>
	<div style=\"padding: 10px; width: 600px; margin: 0 auto; border: 1px solid #a1a1a1;\">
		<div style=\"\">
			<h1 style=\"font-size: 20px; font-weight: bold;\">{TITLE}</h1>
			{CONTENT}
		</div>
		<br /><br />
		<div style=\"float: left;\">
			<strong>Another Service</strong><br />
			<a style=\"color: #56c8f9; text-decoration: none;\" href=\"https://www.anotherservice.com\">https://www.anotherservice.com</a><br />
			<a style=\"color: #56c8f9; text-decoration: none;\" href=\"mailto: contact@anotherservice.com\">contact@anotherservice.com</a>
		</div>
		<div style=\"float: right;\">
			<strong>Support technique</strong><br />
			<a style=\"color: #56c8f9; text-decoration: none;\" href=\"https://support.anotherservice.com/projects/global-support\">https://support.anotherservice.com</a><br />
			<a style=\"color: #56c8f9; text-decoration: none;\" href=\"mailto: support@anotherservice.com\">support@anotherservice.com</a>
		</div>
		<div style=\"clear: both; padding: 2px;\"></div>
	</div>
</body>
</html>";

?>

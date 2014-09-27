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
	
$GLOBALS['CONFIG']['API_HOST'] 		= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	= $conf['Main']['API_TOKEN'];
$GLOBALS['CONFIG']['DOMAIN']		= $conf['Main']['DOMAIN'];
$GLOBALS['CONFIG']['HOSTNAME']		= $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['HOSTNAME_APPS']	= $conf['Main']['HOSTNAME_APPS'];
$GLOBALS['CONFIG']['HOSTNAME_NODE']	= $conf['Main']['HOSTNAME_NODE'];
$GLOBALS['CONFIG']['HOSTNAME_GATE']	= $conf['Main']['HOSTNAME_GATE'];
$GLOBALS['CONFIG']['UPTIME_TOKEN']	= $conf['Main']['UPTIME_TOKEN'];
$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);
unset($file);
unset($domain);

// Box
$GLOBALS['CONFIG']['BOXNET_TOKEN']		= $conf['Apps']['BOXNET_TOKEN'];
$GLOBALS['CONFIG']['BOXNET_SECRET']		= $conf['Apps']['BOXNET_SECRET'];

// Facebook
$GLOBALS['CONFIG']['FACEBOOK_TOKEN']	= $conf['Apps']['FACEBOOK_TOKEN'];
$GLOBALS['CONFIG']['FACEBOOK_SECRET']	= $conf['Apps']['FACEBOOK_SECRET'];

// Twitter
$GLOBALS['CONFIG']['TWITTER_TOKEN']		= $conf['Apps']['TWITTER_TOKEN'];
$GLOBALS['CONFIG']['TWITTER_SECRET']	= $conf['Apps']['TWITTER_SECRET'];

// Google
$GLOBALS['CONFIG']['GOOGLE_TOKEN']		= $conf['Apps']['GOOGLE_TOKEN'];
$GLOBALS['CONFIG']['GOOGLE_SECRET']		= $conf['Apps']['GOOGLE_SECRET'];
$GLOBALS['CONFIG']['GOOGLE_KEY']		= $conf['Apps']['GOOGLE_KEY'];

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/login_action';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'EN';

$GLOBALS['CONFIG']['MAIL_TEMPLATE'] = "
<html>
	<head>
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />
		<style type=\"text/css\">
			a:hover {
				color: #0482e4;
			}
			p {
				margin: 0 0 15px 0;
			}
		</style>
	</head>
	
	<body style=\"background-color: #f5f5f5; font-family: Arial; font-size: 14px;\">
		<div style=\"padding: 20px;\">
			<div style=\"width: 90%; height: 50px; margin: 0 auto;\">
				<img src=\"https://{$GLOBALS['CONFIG']['HOSTNAME']}/busit/images/logo-dark.png\" alt=\"Logo Busit\" style=\"width: 100px;\" />
			</div>
			<div style=\"width: 90%; margin: 0 auto; padding: 10px;	background-color: #ffffff; border: 1px solid #e5e5e5; margin-bottom: 10px;\">
				{CONTENT}
			</div>
			<div style=\"width: 90%; height: 50px;	margin: 0 auto;	color: #9f9f9f;	font-size: 12px;\">
				Copyright &copy; 2014 Busit - <a style=\"color: #005596; text-decoration: none;\" href=\"https://twitter.com/Bus_IT\">Twitter</a> - <a style=\"color: #005596; text-decoration: none;\" href=\"https://facebook.com/busit.net\">Facebook</a>
			</div>
	</body>
</html>
";

?>

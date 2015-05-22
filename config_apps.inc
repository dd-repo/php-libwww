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

$GLOBALS['CONFIG']['API_HOST'] 			= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']		= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']		= $conf['Main']['API_TOKEN'];
$GLOBALS['CONFIG']['RABBIT_HOST']		= $conf['Main']['RABBIT_HOST'];
$GLOBALS['CONFIG']['RABBIT_VHOST']		= $conf['Main']['RABBIT_VHOST'];
$GLOBALS['CONFIG']['RABBIT_USERNAME']	= $conf['Main']['RABBIT_USERNAME'];
$GLOBALS['CONFIG']['RABBIT_PASSWORD']	= $conf['Main']['RABBIT_PASSWORD'];
$GLOBALS['CONFIG']['RABBIT_PORT']		= $conf['Main']['RABBIT_PORT'];
$GLOBALS['CONFIG']['DOMAIN']			= $conf['Main']['DOMAIN'];
$GLOBALS['CONFIG']['HOSTNAME']			= $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['HOSTNAME_APPS']		= $conf['Main']['HOSTNAME_APPS'];
$GLOBALS['CONFIG']['HOSTNAME_NODE']		= $conf['Main']['HOSTNAME_NODE'];
$GLOBALS['CONFIG']['HOSTNAME_GATE']		= $conf['Main']['HOSTNAME_GATE'];
$GLOBALS['CONFIG']['DEBUG'] 			= false;

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/login';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'EN';

unset($conf);
unset($file);
unset($domain);

?>

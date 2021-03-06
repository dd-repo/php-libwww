<?php

class template_on extends template
{
	
	public function __construct()
	{
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_on.lang');
	}
	
	public function error($e)
	{
		$e = $e.'';
		preg_match("/^(.*?)(\\s*Stack trace:\\s*(.*?)\\s*(#.*)?)?$/s", $e, $matches);
		$message = $matches[1];
		
		if( count($matches) > 2 )
			$detail = $matches[3];
		else
			$detail = null;

		if( count($matches) > 3 )
			$stack = $matches[4];
		else $stack = null;

		$_SESSION['MESSAGE']['TYPE'] = 'error';
		$_SESSION['MESSAGE']['TEXT'] = "<p>".security::encode($message, true, true)."</p><strong>".security::encode($detail, true, true)."</strong>";
		
		if( $stack != null )
		{
			$stack = preg_replace("/^#+[0-9\\-]* (.+)$/m", "<li>\$1</li>", $stack);
			$stack = preg_replace("/(\\{main\\}<\\/li>.)/s", "\$1</ol><ol style=\"border-left: 2px solid #E18B7C; margin-top: 10px; margin-bottom: 20px; padding-left: 20px; list-style: decimal inside;\">", $stack);
		}
		
		$this->output();
	}
	
	public function top()
	{		
		$top = "
<!DOCTYPE html>
<html lang=\"{$GLOBALS['CONFIG']['LANGUAGE']}\" xmlns='http://www.w3.org/1999/xhtml' xmlns:v=\"urn:schemas-microsoft-com:vml\">
	<head>
		<title>{$GLOBALS['lang']['TITLE']}</title>
		<meta name=\"description\" content=\"{$GLOBALS['lang']['DESCRIPTION']}\" />
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
		<meta http-equiv=\"Cache-control\" content=\"no-cache\">
		<meta http-equiv=\"Expires\" content=\"-1\">
		<meta name=\"viewport\" content=\"width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no\">
		<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">
		<meta name=\"HandheldFriendly\" content=\"true\">
		<meta name=\"google-site-verification\" content=\"1OLIhe_7AmWyeXDOv31lFstjmkWSD36-EQ2EV8PiDsw\" />
		<meta name=\"wot-verification\" content=\"bfeeaf5dcb8f2cb9418f\" /> 
		
		<meta name=\"twitter:card\" content=\"summary\" />
		<meta name=\"twitter:site\" content=\"@OlympeNet\" />
		<meta name=\"twitter:title\" content=\"Olympe - Free web hosting without ads\" />
		<meta name=\"twitter:description\" content=\"Our non-profit organization offers a free and open-source web hosting, focusing on quality and availability of the services.\" />
		<meta name=\"twitter:image\" content=\"https://www.olympe.in/on/images/logo_email.png\" />
		
		<meta property=\"og:title\" content=\"Olympe - Free web hosting without ads\"/>
		<meta property=\"og:type\" content=\"website\"/>
		<meta property=\"og:url\" content=\"https://www.olympe.in\"/>
		<meta property=\"og:image\" content=\"https://www.olympe.in/on/images/goodies/logo-big.png\"/>
		<meta property=\"og:description\" content=\"Our non-profit organization offers a free and open-source web hosting, focusing on quality and availability of the services.\"/>
		<meta property=\"og:site_name\" content=\"Olympe\"/>
		<meta property=\"fb:admins\" content=\"607747354\"/>
		
		<link rel=\"shortcut icon\" href=\"/{$GLOBALS['CONFIG']['SITE']}/images/favicon.png\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery/jquery-ui-1.10.3.custom.css\" />
		<link rel=\"stylesheet\" href=\"//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css\">
		<link href='https://fonts.googleapis.com/css?family=Roboto:400,100,300' rel='stylesheet' type='text/css'>

		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-1.9.1.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-1.10.3.custom.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-chartjs.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-touch-punch.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-raty.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-jsplumb.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-toggles.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/footer.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/main.js\"></script>";
		
if( strstr($GLOBALS['CONFIG']['PAGE'], 'directory') !== false )
	$top .= "
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/directory.css\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/directory.js\"></script>
	";
if( strstr($GLOBALS['CONFIG']['PAGE'], 'messages') !== false )
	$top .= "
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/messages.css\" type=\"text/css\" />
	";
if( strstr($GLOBALS['CONFIG']['PAGE'], 'doc') !== false )
	$top .= "<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/doc.js\"></script>";
	
$top .= "
	</head>
	<body>
	<div id=\"wrapper\">
		<div id=\"loading\"></div>
		<div class=\"header\">
			<div class=\"content\">
				<div class=\"logo\">
					<a href=\"/\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo.png\" alt=\"logo\" /></a>
				</div>";
				
		$top .= $this->getMainMenu();
			
		$top .= "
			</div>
		</div>
		";
		
		if($GLOBALS['security']->hasAccess('/panel') && (!isset($_COOKIE['logged']) || $_COOKIE['logged'] < time())) {
			$update = api::send('self/user/update', array('last_login_date'=>time(), 'last_login_ip'=>$_SERVER['HTTP_X_REAL_IP']));
			setcookie("logged", time()+300, time()+32745600, "/");
		}
		
		if(!isset($_COOKIE["cookie_agreement"]) || $_COOKIE['cookie_agreement'] != true) {
			if(!isset($_COOKIE["cookie_agreement"]))
				setcookie("cookie_agreement", 1, time()+32745600);
			
			$top .= "
				<div id=\"cookies_warning\">
					{$GLOBALS['lang']['cookie_explain_short']}
					<a href=\"/about?cookie\">{$GLOBALS['lang']['cookie_more']}</a>
					<button onclick=\"$(this).parent().fadeOut();\">{$GLOBALS['lang']['cookie_accept']}</button>
				</div>
			";
		}
		
		$top .= "
		<div id=\"core\" class=\"core ".(strstr($GLOBALS['CONFIG']['PAGE'], 'status')!==false?"status-page":"")."\">";
	
		$logged = $GLOBALS['security']->hasAccess('/panel');

		$top .= $this->getSubMenu();
		
		return $top;
	}

	private function getMainMenu()
	{
		$menu_file = $GLOBALS['CONFIG']['ROOT'].$GLOBALS['CONFIG']['SITE'].'/mainmenu.inc';

		if( file_exists($menu_file) )
		{
			$menu_data = include_once($menu_file);
			$menu = "
			<div class=\"menu\">
					<ul>";

			$logged = $GLOBALS['security']->hasAccess('/panel');
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				$a = $GLOBALS['security']->hasAccess($menu_item['link']);
				if( ($menu_item['anonymous'] && !$logged) || (!$menu_item['anonymous'] && $a) )
				{
					$active = '';
					if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_item['link'], '/')) === 0 ) 
						$active = "class=\"active\"";
					
					if( !$logged && !$menu_item['anonymous'] )
						continue;
					else
					{
						if( is_array($menu_item['sub']) )
						{
							$menu .= "
								<li class=\"{$menu_item['text']}\">
									<a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a>
									<ul>";
								foreach( $menu_item['sub'] as $menu_subitem )
								{
									if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_subitem['link'], '/')) === 0 ) 
										$subactive = "class=\"active\"";
					
									$menu .= "
											<li class=\"{$menu_subitem['text']}\"><a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\" onclick=\"{$menu_subitem['onclick']}\" title=\"\" {$subactive}>{$GLOBALS['lang'][$menu_subitem['text']]}</a></li>";
								}
								
								$menu .= "
									</ul>
								</li>";
						}
						else
						{
							$menu .= "
											<li class=\"{$menu_item['text']}\"><a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a></li>";
						}
					}
				}
			}
			
			$menu .= "
					</ul>
				</div>
			";
			
			return $menu;
		}
		else
			return "";
	}
	
	private function getSubMenu()
	{
		$menu_file = null;
		$path = $GLOBALS['CONFIG']['PATH'];
		while( strlen($path) > strlen($GLOBALS['CONFIG']['ROOT'])-2 )
		{
			if( file_exists($path.'/submenu.inc') )
			{
				$menu_file = $path.'/submenu.inc';
				break;
			}
			else
				$path = dirname($path);
		}
		
		if( $menu_file != null )
		{
			$menu_data = include_once($menu_file);
			$menu = "
					<div class=\"menu-fixed\">
						<div class=\"container\">
							<ul id=\"menu\">
			";
			
			// check which submenu is active
			$active = null;
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				if( $GLOBALS['security']->hasAccess($menu_item['link']) )
				{
					if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_item['link'], '/')) === 0 ) 
						$active = $menu_item['link'];
				}
			}
			
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				if( $GLOBALS['security']->hasAccess($menu_item['link']) )
				{
					$a = '';
					if( $active == $menu_item['link'] || ($active === null && $menu_item['default'] == true) )
						$a = "active";
					
					if( is_array($menu_item['sub']) )
					{
						$menu .= "<li id=\"".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\" class=\"sub ".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\" {$a}><a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\">".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a>
							<ul>";
								
						foreach( $menu_item['sub'] as $menu_subitem )
						{
							if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_subitem['link'], '/')) === 0 ) 
								$subactive = "active";
						
							$menu .= "
								<li class=\"{$menu_subitem['text']} {$subactive}\"><a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\"  onclick=\"{$menu_subitem['onclick']}\" title=\"\">".($GLOBALS['lang'][$menu_subitem['text']]?"{$GLOBALS['lang'][$menu_subitem['text']]}":"{$menu_subitem['text']}")."</a></li>";
						}
									
						$menu .= "
							</ul>
						</li>";
					}
					else
					{
						$menu .= "
									<li id=\"".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\" class=\"{$menu_item['text']} {$a}\"><a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\">".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a></li>
						";
					}
				}
			}
			
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'directory') !== false )
			{
				$menu .= "
									<li id=\"search-li\" class=\"search\"><form id=\"searchform\"><input type=\"submit\" style=\"display: none;\" /><input class=\"auto\" style=\"width: 220px; font-size: 15px;\" type=\"text\" id=\"search\" placeholder=\"{$GLOBALS['lang']['search']}\" /></form></li>";
			}
			
			// admin menu search button
			if( (strstr($GLOBALS['CONFIG']['PAGE'], 'admin') !== false) && ($GLOBALS['security']->hasAccess('/admin')) )
				$menu .= "
									<li id=\"search_admin\" class=\"search_admin\" style=\"float:right!important;\">
										<a id=\"link-search-admin\" href=\"/admin\" onclick=\"$('#search-admin-form').toggle(); return false;\">
											<img src=\"/on/images/search.png\" alt=\"\" style=\"height: 20px;\"/>
										</a>
									</li>
				";

			$menu .= "
								</ul>
							</div>
					</div>";
			
			// admin menu search form
			if( (strstr($GLOBALS['CONFIG']['PAGE'], 'admin') !== false) && ($GLOBALS['security']->hasAccess('/admin')) )
				$menu .= "
					<div id=\"search-admin-form\">
						<div>
							<div class=\"search-admin-form\">
								<form action=\"/admin/search_action\" method=\"post\" id=\"site_search_form\">
									<fieldset>
										<input class=\"auto\" type=\"text\" name=\"name\" placeholder=\"{$GLOBALS['lang']['search_username']}\" />
									</fieldset>
									<fieldset>
										<input class=\"auto\" id=\"site_search_val\" type=\"text\" name=\"site\" placeholder=\"{$GLOBALS['lang']['search_site']}\" />
									</fieldset>
									<fieldset>
										<input class=\"auto\" type=\"text\" name=\"email\" placeholder=\"{$GLOBALS['lang']['search_email']}\" />
									</fieldset>
									<fieldset>
										<input class=\"auto\" type=\"text\" name=\"domain\" placeholder=\"{$GLOBALS['lang']['search_domain']}\" />
									</fieldset>
									<fieldset>
										<input type=\"submit\" value=\"{$GLOBALS['lang']['search_go']}\" />
									</fieldset>					
								</form>
							</div>
						</div>
					</div>
				";
			
			return $menu;
		}
		else
			return "";
	}
	
	public function bottom()
	{
		$bottom = "";
		
		$bottom .= "	
		</div>
		";
		$bottom .= $this->getObjects();
		
		$bottom .= "
			<div id=\"footer\" class=\"footer\">
				<div class=\"content\">
					<div class=\"social\">
						<a class=\"link\" href=\"https://twitter.com/OlympeNet\">
							<span class=\"social_link twitter\"><i class=\"fa fa-twitter\"></i></span>
						</a>
						<a class=\"link\" href=\"https://www.facebook.com/olympe.org\">
							<span class=\"social_link fb\"><i class=\"fa fa-facebook\"></i></span>
						</a>
						<a class=\"link\" href=\"https://google.com/+OlympeIn\">
							<span class=\"social_link google\"><i class=\"fa fa-google-plus\"></i></span>
						</a>
						<a class=\"link\" href=\"https://www.linkedin.com/company/5121206\">
							<span class=\"social_link linkedin\"><i class=\"fa fa-linkedin\"></i></span>
						</a>
						<a class=\"link\" href=\"https://www.youtube.com/channel/UCn1nV97-5DHPIls0_uyP1ig\">
							<span class=\"social_link youtube\"><i class=\"fa fa-youtube-play\"></i></span>
						</a>
						<div class=\"clear\"></div>
					</div>
					<br />
					<ul>
						<li><a href=\"/about\">{$GLOBALS['lang']['ABOUT']}</a></li>
						<li><a href=\"/about/contact\">{$GLOBALS['lang']['CONTACT']}</a></li>
						<li><a href=\"/about/team\">{$GLOBALS['lang']['TEAM']}</a></li>
						<li><a href=\"/doc\">{$GLOBALS['lang']['HELP']}</a></li>
						<li><a href=\"/org/help\">{$GLOBALS['lang']['DONATE']}</a></li>
						<li><a href=\"/directory\">{$GLOBALS['lang']['DIRECTORY']}</a></li>
						<li><a href=\"/developers\">{$GLOBALS['lang']['DEVELOPERS']}</a></li>
						<li><a href=\"/status\">{$GLOBALS['lang']['STATUS']}</a></li>
					</ul>
					<p style=\"margin: 10px 0 0 0; padding: 0; font-size: 12px;\">
	";
	$request = str_replace(array('?lang='.translator::getLanguage(), '&lang='.translator::getLanguage()) , array('', ''), $_SERVER['REQUEST_URI']);

	$bottom .= "	
						".(translator::getLanguage()=='EN'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=EN\">")."English".(translator::getLanguage()=='EN'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
						".(translator::getLanguage()=='FR'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=FR\">")."Fran&ccedil;ais".(translator::getLanguage()=='FR'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
						".(translator::getLanguage()=='ES'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=ES\">")."Espa&ntilde;ol".(translator::getLanguage()=='ES'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
						".(translator::getLanguage()=='DE'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=DE\">")."Deutsch".(translator::getLanguage()=='DE'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
						".(translator::getLanguage()=='IT'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=IT\">")."Italiano".(translator::getLanguage()=='IT'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
					</p>
					<p>{$GLOBALS['lang']['COPYRIGHT']} | {$GLOBALS['lang']['SYS']}</p> 
				</div>
			</div>
		</div>
	";

	$bottom .= "
		<script type=\"text/javascript\">
		  var _paq = _paq || [];
		  _paq.push([\"trackPageView\"]);
		  _paq.push([\"enableLinkTracking\"]);

		  (function() {
			var u=((\"https:\" == document.location.protocol) ? \"https\" : \"http\") + \"://stats.anotherservice.com/\";
			_paq.push([\"setTrackerUrl\", u+\"piwik.php\"]);
			_paq.push([\"setSiteId\", \"67\"]);
			var d=document, g=d.createElement(\"script\"), s=d.getElementsByTagName(\"script\")[0]; g.type=\"text/javascript\";
			g.defer=true; g.async=true; g.src=u+\"piwik.js\"; s.parentNode.insertBefore(g,s);
		  })();
		</script>
		</body>
	</html>";
		
		return $bottom;
	}
	
	private function getObjects()
	{
		if( !isset($_SESSION['ANTISPAM']) )
			$_SESSION['ANTISPAM'] = md5(time().'olympe');

		$objects = "
			<div id=\"login\" class=\"floatingdialog\">
				<div class=\"form-small\">
					<h3 class=\"center\">{$GLOBALS['lang']['login']}</h3>
					<form action=\"/login_action\" method=\"post\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"text\" placeholder=\"{$GLOBALS['lang']['ph_username']}\" name=\"username\" />
								<span class=\"help-block\">{$GLOBALS['lang']['lab_username']}</span>
							</label>
						</fieldset>
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"password\" placeholder=\"***********\" name=\"password\" />
								".(isset($_GET['elogin'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['auth']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['lab_password']}</span>")."
							</label>
						</fieldset>						
						<fieldset>
							<input id=\"remember\" type=\"checkbox\" name=\"remember\" value=\"remember\" />
							<label for=\"remember\" style=\"display: inline-block; padding-left: 10px;\">{$GLOBALS['lang']['remember']}</label>
						</fieldset>
						<fieldset>
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['login']}\" />
						</fieldset>													
					</form>
					<div class=\"clearfix\">&nbsp;</div>
				</div>
			</div>
			<div id=\"login-base\" style=\"display: none;\" class=\"floatingdialog\">
				<div class=\"form-small\">
					<h3 class=\"center\">{$GLOBALS['lang']['login']}</h3>
					<form action=\"/login_action\" method=\"post\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"text\" placeholder=\"{$GLOBALS['lang']['ph_username']}\" name=\"username\" />
								<span class=\"help-block\">{$GLOBALS['lang']['lab_username']}</span>
							</label>
						</fieldset>
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"password\" placeholder=\"{$GLOBALS['lang']['ph_password']}\" name=\"password\" />
								".(isset($_GET['elogin'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['auth']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['lab_password']}</span>")."
							</label>
						</fieldset>							
						<fieldset>
							<input id=\"remember2\" type=\"checkbox\" name=\"remember\" value=\"remember\" />
							<label for=\"remember2\" style=\"display: inline-block; padding-left: 10px;\">{$GLOBALS['lang']['remember']}</label>
						</fieldset>
						<fieldset>
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['login']}\" />
						</fieldset>													
					</form>
					<div class=\"clearfix\">&nbsp;</div>
				</div>
			</div>
			<div id=\"recovery\" style=\"display: none;\" class=\"floatingdialog\">
				<div class=\"form-small\">
					<h3 class=\"center\">{$GLOBALS['lang']['recovery']}</h3>
					<form action=\"/recovery_action\" method=\"post\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"text\" placeholder=\"{$GLOBALS['lang']['ph_username']}\" name=\"username\" />
								".(isset($_GET['erecovery'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['erecovery']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['recoverytips']}</span>")."
							</label>
						</fieldset>
						<fieldset>
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['save']}\" />
						</fieldset>													
					</form>
					<div class=\"clearfix\">&nbsp;</div>
				</div>
			</div>
			<div id=\"signup_lock\" class=\"floatingdialog\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
					<form action=\"/signup_action\" method=\"post\" id=\"signup_valid\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<label class=\"clean\">
								<input style=\"width: 300px;\" class=\"auto\" type=\"text\" placeholder=\"{$GLOBALS['lang']['email']}\" value=\"".($_SESSION['JOIN_EMAIL']?"{$_SESSION['JOIN_EMAIL']}":"")."\" name=\"email\" />
								".(isset($_GET['esignup'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['esignup']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['email_tip']}</span>")."
							</label>
						</fieldset>
						<fieldset>
							<label class=\"clean\">
								<input type=\"checkbox\" name=\"conditions\" value=\"1\" />
								{$GLOBALS['lang']['conditions']}
							</label>
						</fieldset>
						<fieldset>	
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['signup']}\" ".($_SESSION['JOIN_STATUS']===0?'disabled':'')." />
						</fieldset>
					</form>
				</div>
			</div>
			<div id=\"signup\" class=\"floatingdialog\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
					<p class=\"center\">{$GLOBALS['lang']['signup_lock']}</p>
				</div>
			</div>
			<div id=\"register\" class=\"floatingdialog\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
					<p style=\"text-align: center;\">{$GLOBALS['lang']['signup_explain']}</p>
			";
			
			if(isset($_GET['eregister'])) {
				// Get the API error
				$register_error = $_SESSION['REGISTER']['ERROR'];
				$registration_error_num = 0;
				
				// Seek for the issue
				$error_1 = 'Parameter name is not optional';
				$empty_username = strpos($register_error, $error_1);
				
				$error_2 = 'Existing local user';
				$used_username = strpos($register_error, $error_2);
				
				$error_3 = 'Parameter pass is too short';
				$short_pass = strpos($register_error, $error_3);
				
				$error_4 = 'Parameter pass is not optional';
				$empty_pass = strpos($register_error, $error_4);
				
				$error_5 = 'Parameter name does not match';
				$unmatch_username = strpos($register_error, $error_5);
				
				$error_6 = 'Email already exists';
				$used_email = strpos($register_error, $error_6);

				if ($empty_username !== false) 
					$registration_error_num = 1;
				
				if ($used_username !== false) 
					$registration_error_num = 2;
				
				if ($short_pass !== false) 
					$registration_error_num = 3;

				if ($empty_pass !== false) 
					$registration_error_num = 4;
				
				if ($unmatch_username !== false) 
					$registration_error_num = 5;
				
				if ($used_email !== false) 
					$registration_error_num = 6;
				
				$objects .= "
					<hr />
					<span class=\"message error\">". $GLOBALS['lang']['register_error_'. $registration_error_num] ."</span>";				
				
			}
			
		$objects .= "
					<form action=\"/confirm_action\" method=\"post\" id=\"register_valid\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<input type=\"hidden\" name=\"email\" value=\"{$_SESSION['REGISTER']['EMAIL']}\" />
						<input type=\"hidden\" name=\"code\" value=\"{$_SESSION['REGISTER']['CODE']}\" />
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"text\" required placeholder=\"{$GLOBALS['lang']['ph_username']}\" value=\"".($_SESSION['REGISTER']['USERNAME']?"{$_SESSION['REGISTER']['USERNAME']}":"")."\" name=\"username\" />
								<span class=\"help-block\">{$GLOBALS['lang']['usertip']}</span>
							</label>
						</fieldset>
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"password\" required placeholder=\"{$GLOBALS['lang']['ph_password']}\" name=\"password\" />
								<span class=\"help-block\">{$GLOBALS['lang']['lab_password']}</span>
							</label>
						</fieldset>		
						<fieldset>	
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['signup']}\" ".($_SESSION['JOIN_STATUS']===0?'disabled':'')." />
						</fieldset>
					</form>
				</div>
			</div>
			<div id=\"changepass\" class=\"floatingdialog\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['changepass']}</h3>
					<p style=\"text-align: center;\">{$GLOBALS['lang']['changepass_explain']}</p>
					<form action=\"/change_password_action\" method=\"post\" id=\"changepass_valid\" class=\"center\">
						<input type=\"hidden\" name=\"token\" value=\"{$_SESSION['CHANGEPASS']['TOKEN']}\" />
						<input type=\"hidden\" name=\"user\" value=\"{$_SESSION['CHANGEPASS']['USER']}\" />
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"password\" placeholder=\"{$GLOBALS['lang']['ph_password']}\" name=\"password\" />							
								".(isset($_GET['echangepassword'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['echangepassword']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['changetip']}</span>")."
							</label>
						</fieldset>
						<fieldset>
							<label class=\"clean\">
								<input class=\"auto\" type=\"password\" placeholder=\"{$GLOBALS['lang']['confirm']}\" name=\"confirm\" />							
								<span class=\"help-block\">{$GLOBALS['lang']['confirmtip']}</span>
							</label>
						</fieldset>					
						<fieldset>	
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['change']}\" />
						</fieldset>
					</form>
				</div>
				<div id=\"new_CGU\" style=\"display: none; text-align: center;\">
					<br />
					<h3>{$GLOBALS['lang']['new_terms_title']}</h3>
					<p style=\"text-align: center;\">{$GLOBALS['lang']['new_terms_text']}</p>
					<a class=\"button classic\" href=\"/cookie_action\" style=\"width: 180px; height: 22px; margin: 0 auto;\">
						<span style=\"display: block; padding-top: 3px;\">{$GLOBALS['lang']['new_terms_accept']}</span>
					</a>
					<br />
				</div>
			</div>
		";
		
		if( $_SESSION['CHANGEPASS']['TOKEN'] && $_SESSION['CHANGEPASS']['USER'] )
		{
			$objects .= "
						<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#changepass\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>
			";
		}
		
		if( $_SESSION['FORM']['OPEN'] )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#{$_SESSION['FORM']['OPEN']}\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>";
			unset($_SESSION['FORM']['OPEN']);
		}
		
		if( $_SESSION['MESSAGE'] )
		{
			$objects .= "<div id=\"message\">
				<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/notifications/{$_SESSION['MESSAGE']['TYPE']}.png\" /><br />
				<p>{$_SESSION['MESSAGE']['TEXT']}</p>
			</div>
			";
		 }

		if( isset($_GET['elogin']) )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#login\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
							function recovery()
							{
								$(\"#login\").html($('#recovery').html());
							}
							
							function norecovery()
							{
								$(\"#login\").html($('#login-base').html());
							}
						</script>
			";
		}

		if( isset($_GET['erecovery']) )
		{
			$objects .= "<script type=\"text/javascript\">
								$(\"#login\").html($('#recovery').html());
						</script>";
		}
		
		if( $_SESSION['REGISTER']['STATUS'] === true )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#register\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>";	
						
			$_SESSION['REGISTER'] = false;
		}
		
		if( $_SESSION['MESSAGE'] )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#message\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
								setTimeout(\"$('#message').dialog('close')\", 3000);
							});
						</script>";
			
			// we displayed it, clear it
			$_SESSION['MESSAGE'] = false;
		}

		/*if( !$_COOKIE['OLYMPE_CGU_201404']  && $GLOBALS['security']->hasAccess('/panel') )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#cookie\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>";
		}*/
		
		return $objects;
	
	}
}

?>
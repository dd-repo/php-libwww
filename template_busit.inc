<?php

class template_busit extends template
{
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

		$content = "<p>".nl2br($message)."</p><strong>".nl2br($detail)."</strong>";
		
		if( $stack != null )
		{
			$stack = preg_replace("/^#+[0-9\\-]* (.+)$/m", "<li>\$1</li>", $stack);
			$stack = preg_replace("/(\\{main\\}<\\/li>.)/s", "\$1</ol><ol style=\"border-left: 2px solid #E18B7C; margin-top: 10px; margin-bottom: 20px; padding-left: 20px; list-style: decimal inside;\">", $stack);
			$content .= "<ol style=\"border-left: 2px solid #E18B7C; margin-top: 10px; margin-bottom: 20px; padding-left: 20px; list-style: decimal inside;\">";
			$content .= $stack;
			$content .= "</ol>";
		}
		
		$this->output($content);
	}
	
	public function top()
	{
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_busit.lang');
		
		$top = "
<!DOCTYPE html>
<html>
	<head>
		<title>{$GLOBALS['lang']['TITLE']}</title>
		<meta name=\"description\" content=\"{$GLOBALS['lang']['DESCRIPTION']}\" />
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
		<meta http-equiv=\"Cache-control\" content=\"no-cache\">
		<meta http-equiv=\"Expires\" content=\"-1\">
		<link rel=\"shortcut icon\" href=\"https://www.bus-it.com/{$GLOBALS['CONFIG']['SITE']}/img/favicon.ico\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery/jquery-ui-1.10.3.custom.css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-1.9.1.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-1.10.3.custom.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/footer.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/main.js\"></script>
	</head>
	<body>
	<div id=\"wrapper\">
		<div class=\"header\">
			<div class=\"content\">";
		
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') === false )
		{
			$top .="
				<div class=\"logo\">
					<a href=\"/\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo.png\" alt=\"logo\" /></a>
				</div>
			";
		}
		else
		{
			$top .= "
				<div class=\"logo-big\">
					<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo-big.png\" alt=\"logo\" />
				</div>
			";
		}
		
	if( !$GLOBALS['CONFIG']['INSTANCE'] )	
		$top .= $this->getMainMenu();
			
		$top .= "
			</div>
		</div>
";

if( $_SESSION['MESSAGE'] )
{
	$top .= "
		<div id=\"message\">
			<img class=\"icon\" src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/notifications/".($_SESSION['MESSAGE']['TYPE']=='success'?"accept":"error").".png\" />
			{$_SESSION['MESSAGE']['TEXT']}
			<br />
			<div style=\"text-align: right\"><a href=\"#\" onclick=\"document.getElementById('message').style.visibility = 'hidden';\">{$GLOBALS['lang']['DISMISS']}</a></div>
		</div>
	";
	
	// we displayed it, clear it
	$_SESSION['MESSAGE'] = false;
}

$top .= "
		<div class=\"core\">";
	
		$logged = $GLOBALS['security']->hasAccess('/panel');

		if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false  )
		{
			$top .= $this->getSubMenu();
		}
		
		return $top;
	}
	
	private function getMainMenu()
	{
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') === false )
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
						if( preg_match('!^'.rtrim($menu_item['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
							$active = "class=\"active\"";
						
						if( !$logged && !$menu_item['anonymous'] )
							continue;
						else
						{
							if( is_array($menu_item['sub']) )
							{
								$menu .= "
									<li class=\"{$menu_item['text']}\">
										<a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a>
										<ul>";
									foreach( $menu_item['sub'] as $menu_subitem )
									{
										if( preg_match('!^'.rtrim($menu_subitem['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
											$subactive = "class=\"active\"";
						
										$menu .= "
												<li class=\"{$menu_subitem['text']}\"><a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\" title=\"\" {$subactive}>{$GLOBALS['lang'][$menu_subitem['text']]}</a></li>";
									}
									
									$menu .= "
										</ul>
									</li>";
							}
							else
							{
								$menu .= "
							<li class=\"{$menu_item['text']}\"><a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a></li>";
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
					if( preg_match('!^'.rtrim($menu_item['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
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
						$a = "class=\"active\"";

					if( is_array($menu_item['sub']) )
					{
						$menu .= "<li class=\"sub {$menu_item['text']}\"><a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a>
							<ul>";
								
						foreach( $menu_item['sub'] as $menu_subitem )
						{
							if( preg_match('!^'.rtrim($menu_subitem['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
								$subactive = "class=\"active\"";
						
							$menu .= "
								<li class=\"{$menu_subitem['text']}\"><a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\" title=\"\" {$subactive}>{$GLOBALS['lang'][$menu_subitem['text']]}</a></li>";
						}
									
						$menu .= "
							</ul>
						</li>";
					}
					else
					{
						$menu .= "
									<li class=\"{$menu_item['text']}\"><a {$a} href=\"{$menu_item['link']}\">{$GLOBALS['lang'][$menu_item['text']]}</a></li>
						";
					}
				}
			}
			
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false )
			{
				$menu .= "
									<li id=\"search-li\" class=\"search\"><input class=\"auto\" type=\"text\" id=\"search\" value=\"{$GLOBALS['lang']['search']}\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['search']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['search']}' : this.value; this.value=='{$GLOBALS['lang']['search']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" /></li>";
			}
			
			$menu .= "
								</ul>
							</div>
					</div>";
			
			return $menu;
		}
		else
			return "";
	}
	
	public function bottom()
	{
		$bottom = "";
		$logged = $GLOBALS['security']->hasAccess('/panel');
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'help') !== false )
			$bottom .= "</div>";
		
		$bottom .= "	
		</div>
		";
		$bottom .= $this->getObjects();
		
		$bottom .= "

		<div id=\"footer\" class=\"footer\">
			<div class=\"content\">
				<ul>
						<li><a href=\"/about\">{$GLOBALS['lang']['ABOUT']}</a></li>
						<li><a href=\"/about/contact\">{$GLOBALS['lang']['CONTACT']}</a></li>
						<li><a href=\"/doc\">{$GLOBALS['lang']['HELP']}</a></li>
						<li><a href=\"/developers\">{$GLOBALS['lang']['DEVELOPERS']}</a></li>
						<li><a href=\"/about/legal\">{$GLOBALS['lang']['LEGAL']}</a></li>
						<li><a href=\"/about/privacy\">{$GLOBALS['lang']['PRIVACY']}</a></li>
					</ul>
				</ul>
				<p>{$GLOBALS['lang']['COPYRIGHT']}</p>
			</div>
		</div>
	</div>
	<!-- Piwik -->
	<script type=\"text/javascript\">
	  var _paq = _paq || [];
	  _paq.push([\"trackPageView\"]);
	  _paq.push([\"enableLinkTracking\"]);

	  (function() {
		var u=((\"https:\" == document.location.protocol) ? \"https\" : \"http\") + \"://stats.anotherservice.com/\";
		_paq.push([\"setTrackerUrl\", u+\"piwik.php\"]);
		_paq.push([\"setSiteId\", \"9\"]);
		var d=document, g=d.createElement(\"script\"), s=d.getElementsByTagName(\"script\")[0]; g.type=\"text/javascript\";
		g.defer=true; g.async=true; g.src=u+\"piwik.js\"; s.parentNode.insertBefore(g,s);
	  })();
	</script>
	<!-- End Piwik Code -->
	</body>
</html>";
		
		return $bottom;
	}
	
	private function getObjects()
	{
		$objects = "
			<div id=\"login\">
				<div class=\"form-small\">
					<h3 class=\"center\">{$GLOBALS['lang']['login']}</h3>
					<form action=\"/login_action\" method=\"post\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"{$GLOBALS['lang']['username']}\" name=\"username\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['username']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['username']}' : this.value; this.value=='{$GLOBALS['lang']['username']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
						</fieldset>
						<fieldset>
							<input class=\"auto\" type=\"password\" value=\"{$GLOBALS['lang']['password']}\" name=\"password\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['password']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['password']}' : this.value; this.value=='{$GLOBALS['lang']['password']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\"/>
							".(isset($_GET['elogin'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['auth']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['register']}</span>")."
						</fieldset>						
						<fieldset>
							<input type=\"checkbox\" name=\"chbox\" />
							<label for=\"remember\" style=\"display: inline-block; padding-left: 10px;\">{$GLOBALS['lang']['remember']}</label>
						</fieldset>
						<fieldset autofocus>
							<input type=\"submit\" value=\"{$GLOBALS['lang']['login']}\" />
						</fieldset>													
					</form>
					<div class=\"clearfix\">&nbsp;</div>
				</div>
			</div>
			<div id=\"signup\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
					<form action=\"/join_action\" method=\"post\" id=\"valid\" class=\"center\">
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"".($_SESSION['JOIN_USER']?"{$_SESSION['JOIN_USER']}":"{$GLOBALS['lang']['username']}")."\" name=\"username\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['username']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['username']}' : this.value; this.value=='{$GLOBALS['lang']['username']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
							<span class=\"help-block\">{$GLOBALS['lang']['usertip']}</span>
						</fieldset>
						<fieldset>
							<input class=\"auto\" type=\"password\" value=\"{$GLOBALS['lang']['password']}\" name=\"password\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['password']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['password']}' : this.value; this.value=='{$GLOBALS['lang']['password']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\"/>
						</fieldset>		
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"".($_SESSION['JOIN_EMAIL']?"{$_SESSION['JOIN_EMAIL']}":"{$GLOBALS['lang']['email']}")."\" name=\"email\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['email']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['email']}' : this.value; this.value=='{$GLOBALS['lang']['email']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
						</fieldset>
						<fieldset autofocus>	
							<input type=\"submit\" value=\"{$GLOBALS['lang']['signup']}\" ".($_SESSION['JOIN_STATUS']===0?'disabled':'')." />
						</fieldset>
					</form>
				</div>
			</div>
		";
		
				
		if( isset($_GET['elogin']) )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#login\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>
			";
		}
		
		return $objects;
	
	}
}

?>
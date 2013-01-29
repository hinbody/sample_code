<?php
require_once '../whoami.php';
$db_server = mysql_connect($db_host, $db_username, $db_password);

if (!db_server) die("Unable to connect to MySQL: " . mysql_error());

mysql_select_db($db_database, $db_server)
  or die("Unable to select database: " . mysql_error());

if ($_POST['crudFunction'] == 'create')
{
  $player = get_post_var('playersName');
  $position = get_post_var('position');
  $team = get_post_var('team');

  $createPlayer = "INSERT INTO players(name, team, position) VALUES" .
    "('$player', '$team', '$position')";
  if (!mysql_query($createPlayer, $db_server))
    echo "INSERT failed: $createPlayer<br />" .
    mysql_error() . " <br /><br />";
?>
  <script type="text/javascript">
  <!--
  window.location = "../players"
  //-->
  </script>
<?php
}
function get_post_var($postVar)
{
  return mysql_real_escape_string($_POST[$postVar]);
}
?>



<?php  //The following code is what is called after the previous code executes:
require_once '../whoami.php';
$db_server = mysql_connect($db_host, $db_username, $db_password);

if (!db_server) die("Unable to connect to MySQL: " . mysql_error());

mysql_select_db($db_database, $db_server)
  or die("Unable to select database: " . mysql_error());
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <link rel="stylesheet" type="text/css" href="../bootstrap/css/bootstrap.css" />
    <title>Players of That Stuff</title>
  </head>
  <body>
    <div class="hero-unit">
      <h1>That Stuff's Players</h1>
      <p>Here are all the players currently in the system</p>
<?php require_once '../nav.php' ?>
    </div>
<?php
$getAllPlayers = "Select * FROM players";
$allPlayers = mysql_query($getAllPlayers);
$numRows = mysql_num_rows($allPlayers);

for ($i = 0; $i < $numRows; ++$i)
{
  $row = mysql_fetch_row($allPlayers);
echo <<<_PlayerTable
<pre>
 Player Name: $row[0]
        Team: $row[1]
    Position: $row[2]
</pre>
_PlayerTable;
}
?>
  </body>
</html>


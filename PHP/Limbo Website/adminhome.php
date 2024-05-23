<!--
By Andrew Hennessy and Andrew Hatch
-->
<!DOCTYPE html>
<?php
# Includes the header links
require( 'includes/header.php');
echo'<h1>Welcome Admin!</h1>';

# Connect to MySQL server and the database
require( '../connect_db.php' ) ;
?>

<h4>Select A Task</h4>

<p><a href="admin_edit_stuff.php">Change Status of Stuff</a>
<p><a href="admin_delete_stuff.php">Delete Stuff</a>
<p><a href="show_admins.php">View All Admins</a>
<p><a href="admin_new.php">Add New Admin Users</a>
<p><a href="admin_delete_user.php">Delete Admin Users</a>
<p><a href="admin_update.php">Update Admin Users</a>
<p><a href="admin_pass_change.php">Change Password</a>
</html>
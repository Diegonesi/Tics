<?php
include("conexion.php");

$t=$_POST['temperatura'];
$s=$_POST['sonido'];
echo "tiene una temperatura de ".$t." y su bebe ".$s;
date_default_timezone_set('America/Santiago');
$fecha_actual = date("Y-m-d H:i:s");
//echo $fecha_actual;
$consulta = "INSERT INTO tabla_datos(temperatura, sonido, fecha_actual) VALUES ('$t','$s', '$fecha_actual')";
mysqli_query($con,$consulta);

?>

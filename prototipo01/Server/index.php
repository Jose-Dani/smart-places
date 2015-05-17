<?php
	// Combinaciones de parámetros posibles:
	// 1. action=status
	// Retorna un array en json con el estado de cada id. Ejemplo: {"1":"1","2":"0"}
	//
	// 2. action=status&id=1
	// Retorna el valor del estado para el id 1.
	//
	// 3. action=update&id=1&value=0
	// Actualiza el valor del estado del id 1 poniéndolo en 0.

	$dir = "./data";
	$data_file = $dir . "/data.db";

	if(isset($_GET['action']) && !empty($_GET['action'])) {
    $action = $_GET['action'];
    switch($action) {
        case 'status':
        	$data = file_get_contents($data_file);
        	if(isset($_GET['id'])) {
        		$array_data =json_decode($data, true);
        		echo $array_data[$_GET['id']];
        	} else {
	        	echo $data;
        	}
        	break;
    	case 'update': 
    		if(isset($_GET['id']) && isset($_GET['value'])) {
				$data = file_get_contents($data_file);
			
				$array_data =json_decode($data, true);
			
				$array_data[$_GET['id']] = $_GET['value'];
				
				file_put_contents($data_file, json_encode($array_data));
			}
			break;
    	}
    } else {
		echo "Combinaciones de parámetros posibles:<br>";
		echo "1. action=status<br>";
		echo "Retorna un array en json con el estado de cada id. Ejemplo: {\"1\":\"1\",\"2\":\"0\"}.<br><br>";
	
		echo "2. action=status&id=1<br>";
		echo "Retorna el valor del estado para el id 1.<br><br>";
	
		echo "3. action=update&id=1&value=0<br>";
		echo "Actualiza el valor del estado del id 1 poniéndolo en 0.<br>";
    }
?>
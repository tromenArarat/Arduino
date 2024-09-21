<?php
// matriz_led_combinada.php

// Definir las matrices de LED como arrays de bytes
$tipo_camina_1 = [
    "00110000",
    "00110000",
    "00011000",
    "00011000",
    "00011000",
    "00011000",
    "00001000",
    "00001000"
];

$tipo_camina_2 = [
    "00110000",
    "00110000",
    "00011000",
    "00011100",
    "01111110",
    "00111000",
    "00100010",
    "00000010"
];

$tipo_camina_4 = [
    "00110000",
    "00110000",
    "00011100",
    "01111010",
    "00011000",
    "00100100",
    "00100010",
    "00100000"
];

$tipo_camina_5 = [
    "00110000",
    "00110000",
    "00011000",
    "00011000",
    "00111000",
    "00011100",
    "00011000",
    "00010000"
];

// Agrupar todas las matrices en un solo array
$frames = [$tipo_camina_1, $tipo_camina_2, $tipo_camina_4, $tipo_camina_5];
?>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Arduino en pausas</title>
    <style>
        body {
            background-color: #000;
            color: #fff;
            font-family: Arial, sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            padding: 20px;
            box-sizing: border-box;
        }
        h1 {
            margin-bottom: 20px;
        }
        .matrices-container {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 40px;
            width: 100%;
            max-width: 1200px;
        }
        .animated-matrix, .static-matrices {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 20px;
        }
        .matrix {
            display: grid;
            grid-template-columns: repeat(8, 30px);
            grid-template-rows: repeat(8, 30px);
            gap: 5px;
            background-color: #111;
            padding: 10px;
            border-radius: 10px;
        }
        .static-matrix {
            width: 50%;
        }
        .led {
            width: 30px;
            height: 30px;
            background-color: #333;
            border-radius: 50%;
            transition: background-color 0.2s;
        }
        .on {
            background-color: #0f0;
        }
        /* Estilos para matrices estáticas más pequeñas */
        .static-matrices .matrix {
            grid-template-columns: repeat(8, 15px);
            grid-template-rows: repeat(8, 15px);
            gap: 2px;
            padding: 5px;
        }
        .static-matrices .led {
            width: 15px;
            height: 15px;
        }
        @media (max-width: 600px) {
            .matrix {
                grid-template-columns: repeat(8, 20px);
                grid-template-rows: repeat(8, 20px);
                gap: 3px;
            }
            .led {
                width: 20px;
                height: 20px;
            }
            .static-matrices .matrix {
                grid-template-columns: repeat(8, 10px);
                grid-template-rows: repeat(8, 10px);
            }
            .static-matrices .led {
                width: 10px;
                height: 10px;
            }
        }
        .static-matrix-container {
            display: flex;
            flex-direction: row;
            flex-wrap: wrap;
            gap: 10px;
            justify-content: center;
        }
        .static-matrix-wrapper {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 5px;
        }
        .static-matrix-wrapper span {
            font-size: 14px;
            color: #fff;
        }
    </style>
</head>
<body>

<h1>Animación de matriz de leds con referencias estáticas</h1>

<div class="matrices-container">
    <!-- Matriz Principal Animada -->
    <div class="animated-matrix">
        <h2>Matriz animada MAX7219</h2>
        <div class="matrix" id="animated-matrix">
            <?php
            // Generar la cuadrícula de la matriz animada
            for ($row = 0; $row < 8; $row++) {
                for ($col = 0; $col < 8; $col++) {
                    echo '<div class="led" id="animated-led-' . $row . '-' . $col . '"></div>';
                }
            }
            ?>
        </div>
    </div>

    <!-- Matrices Estáticas de Referencia -->
    <div class="static-matrices">
        <h2>Referencias a cuadros estáticos</h2>
        <div class="static-matrix-container">
            <?php
            // Generar las cinco cuadrículas estáticas
            for ($m = 0; $m < count($frames); $m++) {
                echo '<div class="static-matrix-wrapper">';
                echo '<span>Cuadro ' . ($m + 1) . '</span>';
                echo '<div class="matrix static-matrix" id="static-matrix-' . $m . '">';
                for ($row = 0; $row < 8; $row++) {
                    for ($col = 0; $col < 8; $col++) {
                        echo '<div class="led" id="static-led-' . $m . '-' . $row . '-' . $col . '"></div>';
                    }
                }
                echo '</div>';
                echo '</div>';
            }
            ?>
        </div>
    </div>
</div>

<script>
// Obtener las matrices de PHP y convertirlas en arrays de JavaScript
const frames = <?php
    // Convertir las matrices PHP a una estructura JSON
    $js_frames = [];
    foreach ($frames as $frame) {
        $js_frame = [];
        foreach ($frame as $row) {
            $js_frame[] = $row;
        }
        $js_frames[] = $js_frame;
    }
    echo json_encode($js_frames);
?>;

// Configuración de la animación
let currentFrame = 0;
const totalFrames = frames.length;
const delay = 250; // milisegundos

// Función para actualizar la matriz animada
function updateAnimatedMatrix() {
    const frame = frames[currentFrame];
    for (let row = 0; row < 8; row++) {
        const rowData = frame[row];
        for (let col = 0; col < 8; col++) {
            const led = document.getElementById(`animated-led-${row}-${col}`);
            if (led) {
                const bit = rowData.charAt(col) === '1' ? 'on' : '';
                led.className = 'led ' + bit;
            }
        }
    }
    // Avanzar al siguiente cuadro
    currentFrame = (currentFrame + 1) % totalFrames;
}

// Inicializar la matriz animada
setInterval(updateAnimatedMatrix, delay);
updateAnimatedMatrix();

// Función para actualizar las matrices estáticas
function updateStaticMatrices() {
    frames.forEach((frame, index) => {
        for (let row = 0; row < 8; row++) {
            const rowData = frame[row];
            for (let col = 0; col < 8; col++) {
                const led = document.getElementById(`static-led-${index}-${row}-${col}`);
                if (led) {
                    const bit = rowData.charAt(col) === '1' ? 'on' : '';
                    led.className = 'led ' + bit;
                }
            }
        }
    });
}

// Inicializar las matrices estáticas
updateStaticMatrices();
</script>

</body>
</html>

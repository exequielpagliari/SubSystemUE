# SubSystemsUE

Este proyecto implementa una arquitectura basada en Subsystems de Unreal Engine para gestionar el flujo de la aplicación. El objetivo principal es evitar la creación de una clase GameInstance masiva ("God Object"), delegando responsabilidades específicas a módulos independientes y persistentes.

## Arquitectura: Subsystems vs. GameInstance

Para mantener la escalabilidad y limpieza del código, el flujo se divide en diversos subsistemas. Esto permite que cada módulo maneje su propio estado y lógica sin interferir con los demás.

### 1. Subsystems Implementados

SoundSubsystem: Gestiona el control de volumen (Master, Música, SFX) mediante SoundMix y SoundClass overrides. Permite cambios en tiempo real y comunicación directa con la UI.

### 2. RadioSubsystem
Se encarga de la reproducción de música persistente a través de los niveles.
* **Gestión de Playlists:** Utiliza `TArray<TObjectPtr<USoundBase>>` para permitir el uso tanto de SoundWaves como de SoundCues.
* **Audio Espacializado:** Controla un `UAudioComponent` dinámico que se registra en el `World` activo para evitar cortes de audio.
* **Control Logarítmico:** Implementa una función de volumen basada en curvas de potencia ($f(x) = x^2$) para una percepción auditiva natural y profesional.
* **Eventos:** Emite delegados (Multicast Delegates) para notificar a la UI cuando una pista cambia de forma automática.

### 3. GraphicsSubsystem
Punto central para la gestión de la fidelidad visual y el rendimiento del juego.
* **Settings Management:** Accede y modifica los `UGameUserSettings` para ajustar resolución, calidad de texturas, sombras y post-procesado.
* **Abstracción de Comandos:** Expone funciones simples para Blueprints que internamente ejecutan comandos de consola de escalabilidad.
* **Persistencia:** Asegura que los cambios realizados por el usuario se guarden y se apliquen correctamente al iniciar la aplicación.



## Créditos de Audio y Copyright

Este proyecto utiliza recursos de audio externos bajo licencias Creative Commons. A continuación, se detallan los créditos correspondientes para cumplir con los términos de cada autor:

Pista: Temple Procession (ID 1421).
Artista: Lobo Loco.
Álbum: Spaceforce OMEGA.
Licencia: CC BY-NC-SA 4.0.

Pista: A mistake after 37 seconds.
Artista: TR.
Licencia: CC BY-NC-ND 3.0 (Music Sharing).
Nota: Requiere atribución, uso no comercial y no permite obras derivadas.

Pista: keirneuringer.
Artista: Keir Neuringer.
Licencia: CC BY-NC-SA 3.0 US.

Nota: El uso de este material está restringido a fines no comerciales. Cualquier trabajo derivado debe ser compartido bajo la misma licencia.



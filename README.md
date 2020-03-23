# King_test

## Package contents

The package contains the next folders:

- Project: Source code and project.
- Game: Final game version (please use this for test). 
- Game_with_logs: Game compiled with debug logs (just to show it).
- Snapshots: images for this document.

## Tools & Frameworks decisions

The engine provided for this project was used without add any additional asset, because the purpose of this project was show my abilities as C++ Developer and I wanted to be focused on Design and Coding part. Only changes in folder src have been done from the original provided sample project.

## Source structure and design decisions

The source code is divided in the next subfolders:

- **Animation:**  Interfaces and generic code for Animations. In order to decouple animations from GameObjetcs and be able to reuse it, a generic animation engine was implemented.

- **GameBoard:** Representation of the invisible game board where gems are located (8x8 Cell). This GameBoard abstraction was implemented to simply the coordinate system for GameLogic calculations.

- **GameLogic:** Controllers responsible of player interaction and game rules.

- **GameObject:** Interfaces and generic code for GameObjects. This abstraction was implemented because was needed by generic Animation and Render models.

- **Gem**: Implementation of Gem GameObject including: Animations, Renderer, Generator and GameObject. Gems are created as shared pointers due are shared between different classes. The responsible of create Gems and handle Gem destruction is GemGenerator and Gems are allocated in dynamic memory. This shared pointer pattern was chosen due is one of the more simple and was enough for a system that only have 8x8 alive at the same time. This is why other more complex but better performance implementations like Object Pool were discarded. Anyway, if the system grows in the future, GemGenerator is encapsulating Gem creation an destruction, so will not be difficult to replace the Gem memory model.

- **Geometry:** Templatized classes for Geometry representation and calculation: Point, Vector and BBox. The classes have Templatized data type due GameBoard is using data type int and the rest of the code is using data type float, and casting all time from int to float is not a very good practice. 

- **Render:**  Interfaces and generic code for Renderers. Render abstraction was created to decouple game object from OpenGL and Engine; simplify the interfaces and do the update automatically each frame. Two types of RenderController are instantiated:

  - GameRenderController: Is composed by game play objects like Gems, is cleared only when reset application and the resulting objects are rendered down GUIRenderController layer.
  - GameRenderController: Is composed by GUI objects like messages, is cleared every scene change and the resulting objects are rendered up GameRenderController layer.

  Renderers are created as singletons because they need to be static in order to be destroyed after all shared pointers when close application.

- **Scene:** Implementation of the 3 Scenes of the game and scene interface. The game is composed by three scenes:

  - Start Game
  - Game Play
  - End Game

- **Text:** Implementation of Text GameObjct including: Renderer and GameObject. Text objects typically are created by they owner and not shared.

- **Util: **Utilities like:

  - Debug Log, Debug Graphical Text: Designed to help on Game Logic debugging.
  - FPS Display: Designed to check if the system performance is enough.
  - Singleton Template.

## Controls

###Drag and drop

Drop the gem to a valid swap position.

### Selection

A Gem can be selected by clicking it, the selected Gem will be scaled up to indicate that is selected. I'm aware that Gem sprites are not ready for scale, but I used this technique because no selection sprites where provided.

![SelectedGem](Snapshots\SelectedGem.png)

###Timer (additional feature)

The timer indicates player the remaining time to game end. The game duration is 1 minute as indicated in the instructions of this project.

![Timer](Snapshots\Timer.png)

### Score Display (additional feature)

The player can see the score in the top left of the mine door. Each Gem is 1 point as was not requested in the project instructions a score system design/implementation.

![ScoreDisplay](Snapshots\ScoreDisplay.png)

##Debug Tools

###FPS Display (additional feature)

The application have an FPS display at the top left corner to verify the correct performance of frame generation.

![FPS_Display](Snapshots\FPS_Display.png)

###DEBUG_LOG Macro (additional feature)

If the project is compiled with DEBUG_LOG macro defined, the resulting application will print a trace on the output and show gem ids in the game window. Debug compilation mode have this option activated by default.

Find a compiler version with DEBUG_LOG enabled in Game_with_logs folder.

![DEBUG_LOG_Macro](Snapshots\DEBUG_LOG_Macro.png)
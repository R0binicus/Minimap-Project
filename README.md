# Minimap Project

A minimap project that I created in the Unreal Engine, made with C++, as part of my course at CG Spectrum.

For this project, I was given a simple Unreal Engine 3rd-person game, where the player had to complete puzzles by controlling robots. I started off by adding a camera to the player, then using that to render an image onto a widget in the player HUD. However, I did this in under an hour, and I wanted a challenge. Instead, I decided to get an image of the level map, put that into a material render and scale and offset it at runtime so it tracked the player and camera. I had this running fairly quickly, with the biggest time sink being getting the math just right.

The next step was to add minimap icons, which would track the location of the robots the player wasn’t controlling. The big issue was that the entire game I was given was in blueprints, and the robots were no exception. This meant it would be difficult to access data or add new implementation to the robots with C++. To get around this, I made a C++ minimap icon tracker interface, which would get added to a weak pointer array in a C++ subsystem when the robots were created. I had an extra challenge doing this, as I needed to implement the C++ interface directly onto the blueprint. Essentially, because the TScriptInterface was implemented on a blueprint, rather than a C++ script, when I tried to access the interface, it would always return nullptr. The way around this was to store the interface as a UObject directly, then access the interface function without a cast. I found this page especially helpful when figuring that out: https://www.stevestreeting.com/2020/11/02/ue4-c-interfaces-hints-n-tips/ 

After this, I still had a bunch of time left, so I implemented some optimisations. One of the many optimisations I did was object pooling of the minimap icons. This was far better than the cruder alternative, where I had at one point deleted and recreated each icon every tick of the game (gross! But it was quick to implement). Instead, I pre-made the icons that the robots would be using. I then hid the icons, then enabled them when they needed to be used, and swapped which robot the icon was tracking when a robot was destroyed/created.


If I had the opportunity to do this again, I would probably try to add more features, such as a full map window and map settings. I would also try to do some optimisations, including rendering the icons directly on the minimap image, rather than UMG widgets over the top of the minimap image (which seems to have a bit of a drawing delay). However, rather than adding lots of little features, my main goal for this was practice and learning, and in that, I have definitely succeeded. Plus, I had a great time while doing so!

## Key Features

- **Map Image Rendering** – Utilises image of the level map in a material, which is then scaled and offset to zoom into where the player is.
- **Player Follow** – Minimap is always centered  where the player is as they move around the level.
- **Cameera Tracking** – Minimap tracks the player camera to make sure it always faces the same angle as the camera.
- **Minimap Icons** – Minimap icons are present, which track the robots around the level as the player moves around.
- **Object Pooling** – Minimap icons use object pooling to prevent the uneeded, expensive creation of icon objects.
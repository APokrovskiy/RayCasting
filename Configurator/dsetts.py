import sclasses


TEXT_MAP = (
    "1111111111111111111111",
    "1000000000000000000001",
    "1000000000000000000001",
    "1000000000000000000001",
    "1000000000000000000001",
    "1000000000000000000001",
    "1000000000000000000001",
    "1000000000000000000001",
    "1000000000000000000001",
    "1000000000000000000001",
    "1111111111111111111111"
)

FPS = 60

CAMERA = sclasses.Settings.Camera(
    position = (250, 250),
    speed = 3,
    n_rays = 100,
    visual_range = 3000,
    rot_speed = 0.01
)

WIDGETS = sclasses.Settings.Visible_widgets(
    minimap = True,
    fps = False
)

SETTINGS = sclasses.Settings(CAMERA, WIDGETS, FPS, TEXT_MAP)
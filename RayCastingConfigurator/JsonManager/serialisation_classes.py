# Классы для сериализации настроек в json
class Window:
    def __init__(self, title, screen_size: tuple, fps_limit) -> None:
        self.title = title
        self.screen_size = screen_size
        self.fps_limit = fps_limit
        self.__is_valid()

    def __init__(self, dictionary):
        self.title = dictionary["title"]
        self.screen_size = dictionary["screen_size"]
        self.fps_limit = dictionary["fps_limit"]
        self.__is_valid()
    
    def __is_valid(self):
        if self.screen_size[0] <= 0: 
            raise ValueError("World.screen_size[0] <= 0")
        elif self.screen_size[1] <= 0:
            raise ValueError("World.screen_size[1] <= 0")
        if len(self.screen_size) != 2:
            raise ValueError("len(World.screen_size) != 2")
        if self.fps_limit <= 0: 
            raise ValueError("World.fps_limit <= 0")



class World:
    def __init__(self, world_map: tuple[str], wall_char,
                 tile_size: int) -> None:
        self.world_map = world_map
        self.wall_char = wall_char
        self.tile_size = tile_size
        self.__is_valid()
        
    def __init__(self, dictionary):
        self.world_map = dictionary["world_map"]
        self.wall_char = dictionary["wall_char"]
        self.tile_size = dictionary["tile_size"]
        self.__is_valid()

    def __is_valid(self):
        if self.tile_size <= 0: 
            raise ValueError("World.tile_size <= 0")

class Camera:
    def __init__(self, position: tuple, speed: float,
                 rotation_angle: float, n_rays: int, 
                 visual_range: int, field_of_view: float) -> None:
        self.position = position
        self.speed = speed
        self.rotation_angle = rotation_angle
        self.n_rays = n_rays
        self.visual_range = visual_range
        self.field_of_view = field_of_view
        self.__is_valid()

    def __init__(self, dictionary):
        self.position = dictionary["position"]
        self.speed = dictionary["speed"]
        self.rotation_angle = dictionary["rotation_angle"]
        self.n_rays = dictionary["n_rays"]
        self.visual_range = dictionary["visual_range"]
        self.field_of_view = dictionary["field_of_view"]
        self.__is_valid()

    def __is_valid(self):
        if self.speed < 0: 
            raise ValueError("Camera.speed < 0")
        if self.n_rays <= 0: 
            raise ValueError("Camera.n_rays <= 0")
        if self.visual_range <= 0:
            raise ValueError("Camera.visual_range <= 0")
        if self.field_of_view <= 0:
            raise ValueError("Camera.field_of_view <= 0")

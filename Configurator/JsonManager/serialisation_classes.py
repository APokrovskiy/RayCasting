from typing import Tuple

# Классы для сериализации настроек в json
class Window:
    def __init__(self, title=None, screen_size=None, fps_limit=None, dictionary=None) -> None:
        if dictionary:
            self.title = dictionary.get("title", title)
            self.screen_size = dictionary.get("screen_size", screen_size)
            self.fps_limit = dictionary.get("fps_limit", fps_limit)
        else:
            self.title = title
            self.screen_size = screen_size
            self.fps_limit = fps_limit

        self.__is_valid()

    def __is_valid(self):
        if self.screen_size is not None and self.fps_limit is not None:
            if self.screen_size[0] <= 0 or self.screen_size[1] <= 0:
                raise ValueError("Недопустимый размер экрана")
            if len(self.screen_size) != 2:
                raise ValueError("Размер экрана должен быть кортежем длиной 2")
            if self.fps_limit <= 0:
                raise ValueError("Предел кадров в секунду должен быть больше 0")
        else:
            raise ValueError("Размер экрана или предел кадров в секунду не предоставлен или имеет значение None")



class World:
    def __init__(self, world_map: Tuple[str] = None, wall_char=None, tile_size: int=None, dictionary = None) -> None:
        if(dictionary):
            self.world_map = dictionary["world_map"]
            self.wall_char = dictionary["wall_char"]
            self.tile_size = dictionary["tile_size"]
        else:
            self.world_map = world_map
            self.wall_char = wall_char
            self.tile_size = tile_size
        self.__is_valid()
        

    def __is_valid(self):
        if self.tile_size <= 0: 
            raise ValueError("World.tile_size <= 0")

class Camera:
    def __init__(self, position: tuple = None, speed: float = None,
                 rotation_angle: float = None, n_rays: int = None, 
                 visual_range: int = None, field_of_view: float = None, dictionary = None) -> None:
        if(dictionary):
            self.position = dictionary["position"]
            self.speed = dictionary["speed"]
            self.rotation_angle = dictionary["rotation_angle"]
            self.n_rays = dictionary["n_rays"]
            self.visual_range = dictionary["visual_range"]
            self.field_of_view = dictionary["field_of_view"]
        else:
            self.position = position
            self.speed = speed
            self.rotation_angle = rotation_angle
            self.n_rays = n_rays
            self.visual_range = visual_range
            self.field_of_view = field_of_view
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

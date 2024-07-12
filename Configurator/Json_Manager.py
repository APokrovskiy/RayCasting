import json

import os
import sclasses

class Json_Manager:
    def __init__(self, title:str) -> None:
        if(os.path.exists(title)):
            self.title = title
        else: raise FileExistsError(title + " not exists")

    def to_json(self, settings: sclasses.Settings):
        data = settings.to_dict()
        with open(self.title, "w") as config:
            json.dump(data, config, indent=4)

    def from_json(self) -> sclasses.Settings:
        data = None
        with open(self.title, "r") as f:
            data = json.load(f)
        return sclasses.Settings(dictionary = data)


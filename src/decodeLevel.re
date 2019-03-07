type levelResponse = {
  idLevel: int,
  grade: string,
  level: int,
  nbEcts: int,
  titre: string,
};

type response = {
  success: bool,
  token: string,
  profile: levelResponse,
  message: string,
};

let decodeProfile = json =>
  Json.Decode.{
    idLevel: json |> field("idLevel", int),
    grade: json |> field("grade", string),
    level: json |> field("level", int),
    nbEcts: json |> field("nbEcts", int),
    titre: json |> field("titre", string),
  };

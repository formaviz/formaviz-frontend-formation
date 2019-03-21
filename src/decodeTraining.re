type levelResponse = {
  idLevel: int,
  grade: string,
  level: int,
  nbEcts: int,
  titre: string,
};
type trainingResponse = {
  idFormation: string,
  name: option(string),
  description: option(string),
  admLevel: option(list(levelResponse)),
  diplomaLevel: levelResponse,
  expertise: option(string),
  partTime: option(bool),
  logoPath: option(string),
  link: option(string),
  duration: string,
  schoolName: string,
  schoolDescription: option(string),
  schoolPostalcode: string,
  schoolCity: option(string),
  lowestScore: option(int),
  highestScore: option(int),
  averageScore: option(float),
};

type response = {
  success: option(bool),
  token: option(string),
  profile: trainingResponse,
  message: option(string),
};
let decodeLevel = json =>
  Json.Decode.{
    idLevel: json |> field("idLevel", int),
    grade: json |> field("grade", string),
    level: json |> field("level", int),
    nbEcts: json |> field("nbEcts", int),
    titre: json |> field("titre", string),
  };
let decodeProfile = json =>
  Json.Decode.{
    idFormation: json |> field("idFormation", string),
    name: json |> field("name", optional(string)),
    description: json |> optional(field("description", string)),
    admLevel:
      json |> optional(field("admLevel", Json.Decode.list(decodeLevel))),
    diplomaLevel: json |> field("diplomaLevel", decodeLevel),
    expertise: json |> optional(field("expertise", string)),
    partTime: json |> optional(field("partTime", bool)),
    logoPath: json |> optional(field("logoPath", string)),
    link: json |> optional(field("link", string)),
    duration: json |> field("duration", string),
    schoolName: json |> field("schoolName", string),
    schoolDescription: json |> optional(field("schoolDescription", string)),
    schoolPostalcode: json |> field("schoolPostalCode", string),
    schoolCity: json |> optional(field("schoolCity", string)),
    lowestScore: json |> optional(field("lowestScore", int)),
    highestScore: json |> optional(field("highestScore", int)),
    averageScore: json |> optional(field("averageScore", float)),
  };

let decodeLevels = json => Json.Decode.list(decodeLevel, json);

let decodeTrainings = json => Json.Decode.list(decodeProfile, json);

let decodeResponse = json => {
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    token: json |> optional(field("token", string)),
    profile: json |> field("profile", decodeProfile),
    message: json |> optional(field("message", string)),
  };
};

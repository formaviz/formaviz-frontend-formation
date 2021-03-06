type levelResponse = {
  idLevel: int,
  grade: string,
  level: int,
  nbECTS: int,
  title: string,
};

let decodeLevel = json =>
  Json.Decode.{
    idLevel: json |> field("idLevel", int),
    grade: json |> field("grade", string),
    level: json |> field("level", int),
    nbECTS: json |> field("nbECTS", int),
    title: json |> field("title", string),
  };

type responseLevel = {
  success: option(bool),
  levels: list(levelResponse),
  message: option(string),
};

let decodeLevelResponse = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    levels: json |> field("levels", Json.Decode.list(decodeLevel)),
    message: json |> optional(field("message", string)),
  };
type singleResponseLevel = {
  success: option(bool),
  singlelevels: levelResponse,
  message: option(string),
};

type trainingResponse = {
  idTraining: string,
  name: option(string),
  description: option(string),
  admLevel: option(list(int)),
  diplomaLevel: int,
  expertise: option(string),
  partTime: option(bool),
  logoPath: option(string),
  link: option(string),
  duration: int,
  schoolName: string,
  schoolDescription: option(string),
  schoolPostalcode: int,
  schoolCity: option(string),
  lowestScore: option(int),
  highestScore: option(int),
  averageScore: option(float),
};
type trainingType = {training: trainingResponse};

type response = {
  success: option(bool),
  token: option(string),
  trainings: list(trainingType),
  message: option(string),
};

type singleResponse = {
  success: option(bool),
  token: option(string),
  singleTraining: trainingResponse,
  message: option(string),
};

let decodeProfile = json =>
  Json.Decode.{
    idTraining: json |> field("idTraining", string),
    name: json |> field("name", optional(string)),
    description: json |> optional(field("description", string)),
    admLevel: json |> optional(field("admLevel", Json.Decode.list(int))),
    diplomaLevel: json |> field("diplomaLevel", int),
    expertise: json |> optional(field("expertise", string)),
    partTime: json |> optional(field("partTime", bool)),
    logoPath: json |> optional(field("logoPath", string)),
    link: json |> optional(field("link", string)),
    duration: json |> field("duration", int),
    schoolName: json |> field("schoolName", string),
    schoolDescription: json |> optional(field("schoolDescription", string)),
    schoolPostalcode: json |> field("schoolPostalCode", int),
    schoolCity: json |> optional(field("schoolCity", string)),
    lowestScore: json |> optional(field("lowestScore", int)),
    highestScore: json |> optional(field("highestScore", int)),
    averageScore: json |> optional(field("averageScore", float)),
  };

let decodeTrainings = json =>
  Json.Decode.{training: json |> field("training", decodeProfile)};

let decodeResponse = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    token: json |> optional(field("token", string)),
    trainings: json |> field("trainings", Json.Decode.list(decodeTrainings)),
    message: json |> optional(field("message", string)),
  };

let decodeSingleResponse = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    token: json |> optional(field("token", string)),
    singleTraining: json |> field("training", decodeProfile),
    message: json |> optional(field("message", string)),
  };

let decodeSingleCreatedTraining = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    token: json |> optional(field("token", string)),
    singleTraining: json |> field("profile", decodeProfile),
    message: json |> optional(field("message", string)),
  };

let encodeListLevel = (admLevel: option(list(int))) =>
  admLevel |> Json.Encode.nullable(Json.Encode.list(Json.Encode.int));
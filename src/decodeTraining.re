type levelResponse = {
  idLevel: int,
  grade: string,
  level: int,
  nbEcts: int,
  titre: string,
};

type trainingResponse = {
  idTraining: string,
  name: option(string),
  description: option(string),
  admLevel: option(list(levelResponse)),
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

type levelsResponse = {
  success: option(bool),
  levels: list(levelResponse),
  message: option(string),
};
type singleResponse = {
  success: option(bool),
  token: option(string),
  singleTraining: trainingResponse,
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
    idTraining: json |> field("idTraining", string),
    name: json |> field("name", optional(string)),
    description: json |> optional(field("description", string)),
    admLevel:
      json |> optional(field("admLevel", Json.Decode.list(decodeLevel))),
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

let decodeLevelResponse = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    levels: json |> field("trainings", Json.Decode.list(decodeLevel)),
    message: json |> optional(field("message", string)),
  };

let decodeSingleResponse = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    token: json |> optional(field("token", string)),
    singleTraining: json |> field("training", decodeProfile),
    message: json |> optional(field("message", string)),
  };

/* let encodeLevel = (level: levelResponse) =>
     Json.Encode.encoder(id, level.idLevel);

   let encodeLevelList = ([head, ...queue]: list(levelResponse)) =>
     Json.Encode.list([encodeLevel(head), ...encodeLevelList(queue)]); */

let encodeTraining = (trainingResp: trainingResponse) =>
  Json.Encode.(
    object_(
      [],
        /* (
             "name",
             string(
               switch (trainingResp.name) {
               | Some(value) => value
               },
             ),
           ),
           (
             "description",
             string(
               switch (trainingResp.description) {
               | Some(value) => value
               },
             ),
           ),
           (
             "admLevel",
             encodeLevelList(
               switch (trainingResp.admLevel) {
               | Some(list) => list
               },
             ),
           ),
           ("diplomaLevel", int(trainingResp.diplomaLevel)),
           (
             "expertise",
             string(
               switch (trainingResp.expertise) {
               | Some(value) => value
               },
             ),
           ),
           (
             "partTime",
             bool(
               switch (trainingResp.partTime) {
               | Some(value) => value
               },
             ),
           ),
           (
             "logoPath",
             string(
               switch (trainingResp.logoPath) {
               | Some(value) => value
               },
             ),
           ),
           (
             "link",
             string(
               switch (trainingResp.link) {
               | Some(value) => value
               },
             ),
           ),
           ("duration", string(trainingResp.duration)),
           ("schoolName", string(trainingResp.schoolName)),
           (
             "schoolDescription",
             string(
               switch (trainingResp.schoolDescription) {
               | Some(value) => value
               },
             ),
           ),
           ("schoolPostalcode", string(trainingResp.schoolPostalcode)),
           (
             "schoolCity",
             string(
               switch (trainingResp.schoolCity) {
               | Some(value) => value
               },
             ),
           ),
           (
             "lowestScore",
             int(
               switch (trainingResp.lowestScore) {
               | Some(value) => value
               },
             ),
           ),
           (
             "highestScore",
             int(
               switch (trainingResp.highestScore) {
               | Some(value) => value
               },
             ),
           ),
           (
             "averageScore",
             float(
               switch (trainingResp.averageScore) {
               | Some(value) => value
               },
             ),
           ), */
    )
  );
open DecodeLevel;

type trainingResponse = {
  idFormation: string,
  name: option(string),
  description: option(string),
  admLevel: option(levelResponse),
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
  success: bool,
  token: string,
  profile: trainingResponse,
  message: string,
};

let decodeProfile = json =>
  Json.Decode.{
    idFormation: json |> field("idFormation", string),
    name: json |> field("name", optional(string)),
    description: json |> field("description", optional(string)),
    admLevel: json |> field("admlevel", optional(DecodeLevel.decodeProfile)),
    diplomaLevel: json |> field("diplomaLevel", DecodeLevel.decodeProfile),
    expertise: json |> field("expertise", optional(string)),
    partTime: json |> field("partTime", optional(bool)),
    logoPath: json |> field("logoPath", optional(string)),
    link: json |> field("link", optional(string)),
    duration: json |> field("duration", string),
    schoolName: json |> field("schoolName", string),
    schoolDescription: json |> field("schoolDescription", optional(string)),
    schoolPostalcode: json |> field("schoolPostalcode", string),
    schoolCity: json |> field("schoolCity", optional(string)),
    lowestScore: json |> field("lowestScore", optional(int)),
    highestScore: json |> field("highestScore", optional(int)),
    averageScore: json |> field("averageScore", optional(float)),
  };

let decodeResponse = json => {
    Json.Decode.{
      success: json |> field("success", bool),
      token: json |> field("token", string),
      profile: json |> field("profile", decodeProfile),
      message: json |> field("message", string),
    };
}


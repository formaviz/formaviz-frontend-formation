type ratingResponse = {
  idRating: string,
  comment: string,
  score: int,
  trainingId: string,
  userOfRating: string,
};

type ratingType = {rating: ratingResponse};

type response = {
  success: option(bool),
  token: option(string),
  ratings: list(ratingType),
  message: option(string),
};

type singleResponse = {
  success: option(bool),
  token: option(string),
  singleRating: ratingResponse,
  message: option(string),
};

let decodeRating = json =>
  Json.Decode.{
    idRating: json |> field("idRating", string),
    comment: json |> field("comment", string),
    score: json |> field("score", int),
    trainingId: json |> field("trainingId", string),
    userOfRating: json |> field("userOfRating", string),
  };

let decodeRatings = json =>
  Json.Decode.{rating: json |> field("training", decodeRating)};

let decodeResponse = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    token: json |> optional(field("token", string)),
    ratings: json |> field("ratings", Json.Decode.list(decodeRatings)),
    message: json |> optional(field("message", string)),
  };

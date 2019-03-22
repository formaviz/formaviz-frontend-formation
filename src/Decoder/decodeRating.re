type ratingResponse = {
  idRating: string,
  comment: string,
  score: int,
  idTraining: string,
};

type ratingType = {rating: ratingResponse};

type response = {
  success: option(bool),
  ratings: list(ratingResponse),
  message: option(string),
};

type singleResponse = {
  success: option(bool),
  singleRating: ratingResponse,
  message: option(string),
};

let decodeRating = json =>
  Json.Decode.{
    idRating: json |> field("idRate", string),
    comment: json |> field("comment", string),
    score: json |> field("score", int),
    idTraining: json |> field("idTraining", string),
  };

let decodeRatingComment = json =>
  Json.Decode.{
    idRating: json |> field("idRating", string),
    comment: json |> field("comment", string),
    score: json |> field("score", int),
    idTraining: json |> field("trainingId", string),
  };

let decodeRatings = json =>
  Json.Decode.{rating: json |> field("ratings", decodeRating)};

let decodeResponse = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    ratings: json |> field("ratings", Json.Decode.list(decodeRating)),
    message: json |> optional(field("message", string)),
  };

let decodeResponseSend = json =>
  Json.Decode.{
    success: json |> optional(field("success", bool)),
    singleRating: json |> field("rating", decodeRatingComment),
    message: json |> optional(field("message", string)),
  };

let encodeRating = (ratingResponse: ratingResponse) =>
  Json.Encode.(
    object_([
      ("comment", string(ratingResponse.comment)),
      ("score", int(ratingResponse.score)),
      ("idTraining", string(ratingResponse.idTraining)),
    ])
  );
/*Json.Encode.(
    object_([
      ("comment", string(ratingResponse.comment)),
      ("score", int(ratingResponse.score)),
      ("idTraining", string(ratingResponse.trainingId)),
    ])
  )*/

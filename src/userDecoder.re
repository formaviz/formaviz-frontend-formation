type userLogin = {
  success: bool,
  access_token: string,
};

let decodeUserLogin = json => {
  let user =
    Json.Decode.{
      success: json |> field("success", bool),
      access_token: json |> field("access_token", string),
    };
  SessionUser.saveUser(user.access_token);
};
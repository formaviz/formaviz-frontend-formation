open SessionUser;
open DecodeTraining;
open Config;

let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");

let url_dev: string = "http://localhost:8080/";
let initialLevel = {idLevel: 0, grade: "", level: 0, nbEcts: 0, titre: ""};

let initialtraining = {
  idTraining: "",
  name: Some(""),
  description: Some(""),
  admLevel: Some([initialLevel]),
  diplomaLevel: 0,
  expertise: Some(""),
  partTime: Some(false),
  logoPath: Some(""),
  link: Some(""),
  duration: 0,
  schoolName: "",
  schoolDescription: Some(""),
  schoolPostalcode: 0,
  schoolCity: Some(""),
  lowestScore: Some(0),
  highestScore: Some(0),
  averageScore: Some(0.0),
};
type state = {
  trainingResponse: DecodeTraining.trainingResponse,
  levels: list(DecodeTraining.levelResponse),
  error: string,
};

type action =
  | UpdateNameField(string)
  | UpdateDescriptionField(string)
  | UpdateExpertiseField(string)
  | UpdatePartTimeField(bool)
  | UpdateLogoPath(string)
  | UpdateLinkField(string)
  | UpdateDurationField(string)
  | UpdateSchoolNameField(string)
  | UpdateSchoolDescriptionField(string)
  | UpdateSchoolPostalCodeField(string)
  | UpdateSchoolCityField(string)
  | CreateTraining
  | LoadedLevels(list(DecodeTraining.levelResponse));

let select_partTime = (event, self) =>
  switch (ReactEvent.Form.target(event)##value) {
  | "true" => self.ReasonReact.send(UpdatePartTimeField(true))
  | "false" => self.send(UpdatePartTimeField(false))
  | _ => self.send(UpdatePartTimeField(false))
  };

let handleChange = event => Js.log(ReactEvent.Form.target(event)##value);

let component = ReasonReact.reducerComponent("createTraining");

let make = _children => {
  let sendTraining = state =>
    Js.Promise.(
      Fetch.fetchWithInit(
        Config.url_back ++ "/trainings",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=
            Fetch.BodyInit.make(
              Js.Json.stringify(
                DecodeTraining.encodeTraining(state.trainingResponse),
              ),
            ),
          ~headers=
            Fetch.HeadersInit.make({
              "Content-Type": "application/json",
              "Authorization": "Bearer " ++ SessionUser.getToken,
            }),
          (),
        ),
      )
      |> then_(Fetch.Response.json)
      |> then_(json =>
           json
           |> DecodeRating.decodeResponseSend
           |> (resp => Some(resp) |> resolve)
         )
    );
  let getLevels = self =>
    Js.Promise.(
      Fetch.fetchWithInit(
        Config.url_back ++ "/levels",
        Fetch.RequestInit.make(
          ~method_=Get,
          ~headers=
            Fetch.HeadersInit.make({
              "Content-Type": "application/json",
              "Authorization": "Bearer " ++ SessionUser.getToken,
            }),
          (),
        ),
      )
      |> Js.Promise.then_(Fetch.Response.json)
      |> Js.Promise.then_(json =>
           json
           |> DecodeTraining.decodeLevelResponse
           |> (result => self.ReasonReact.send(LoadedLevels(result.levels)))
           |> Js.log
           |> resolve
         )
    )
    |> ignore;
  {
    ...component,
    initialState: () => {
      trainingResponse: initialtraining,
      levels: [],
      error: "",
    },
    reducer: (action, state) =>
      switch (action) {
      | UpdateNameField(name) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            name,
          },
        })
      | UpdateDescriptionField(description) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            description,
          },
        })
      | UpdateExpertiseField(expertise) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            expertise,
          },
        })
      | UpdatePartTimeField(partTime) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            partTime,
          },
        })
      | UpdateLogoPath(logoPath) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            logoPath,
          },
        })
      | UpdateLinkField(link) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            link,
          },
        })
      | UpdateDurationField(duration) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            duration,
          },
        })
      | UpdateSchoolNameField(schoolName) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            schoolName,
          },
        })
      | UpdateSchoolDescriptionField(schoolDescription) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            schoolDescription,
          },
        })
      | UpdateSchoolPostalCodeField(schoolPostalCode) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            schoolPostalCode,
          },
        })
      | UpdateSchoolCityField(schoolCity) =>
        ReasonReact.Update({
          ...state,
          trainingResponse: {
            ...state.trainingResponse,
            schoolCity,
          },
        })
      | CreateTraining => ReasonReact.NoUpdate
      | LoadedLevels(value) => ReasonReact.Update({...state, levels: value})
      },
    render: _self =>
      <div className="card align-middle mx-auto w-50 p-3 text-center col-12">
        <form>
          <div className="card-header">
            (ReasonReact.string({js|Création d'une formation|js}))
          </div>
          <div className="card-body">
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=(
                  switch (_self.state.name) {
                  | Some(value) => value
                  | None => ""
                  }
                )
                placeholder="Nom de la formation"
                onChange=(
                  event =>
                    _self.send(
                      UpdateNameField(ReactEvent.Form.target(event)##value),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=(
                  switch (_self.state.description) {
                  | Some(value) => value
                  | None => ""
                  }
                )
                placeholder="Description de la formation"
                onChange=(
                  event =>
                    _self.send(
                      UpdateDescriptionField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=(
                  switch (_self.state.expertise) {
                  | Some(value) => value
                  | None => ""
                  }
                )
                placeholder="Niveau d'expertise"
                onChange=(
                  event =>
                    _self.send(
                      UpdateExpertiseField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <div className="input-group-prepend">
                <span className="input-group-text" id="">
                  (ReasonReact.string("Alternance :"))
                </span>
              </div>
              <select
                className="form-control"
                id="pet-select"
                onChange=(event => select_partTime(event, _self))>
                <option value="">
                  (ReasonReact.string("Choix d'une option"))
                </option>
                <option value="true"> (ReasonReact.string("Oui")) </option>
                <option value="false"> (ReasonReact.string("Non")) </option>
              </select>
            </div>
            <div className="input-group mb-3">
              <div className="input-group-prepend">
                <span className="input-group-text" id="">
                  (ReasonReact.string("Url de la photo :"))
                </span>
              </div>
              <input
                className="form-control"
                type_="text"
                placeholder="http://www.img.test/img"
                onChange=(
                  event =>
                    _self.send(
                      UpdateLogoPath(ReactEvent.Form.target(event)##value),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=(
                  switch (_self.state.link) {
                  | Some(value) => value
                  | None => ""
                  }
                )
                placeholder={js|lien du site de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateLinkField(ReactEvent.Form.target(event)##value),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="number"
                value=(string_of_int(_self.state.duration))
                placeholder={js|Durée de la formation|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateDurationField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=_self.state.schoolName
                placeholder={js|Nom de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolNameField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=(
                  switch (_self.state.schoolDescription) {
                  | Some(value) => value
                  | None => ""
                  }
                )
                placeholder={js|Description de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolDescriptionField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=(string_of_int(_self.state.schoolPostalcode))
                placeholder={js|Code postale de la ville de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolPostalCodeField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
            <div className="input-group mb-3">
              <input
                className="form-control"
                type_="text"
                value=(
                  switch (_self.state.schoolCity) {
                  | Some(value) => value
                  | None => ""
                  }
                )
                placeholder={js|Nom de la ville de l'école|js}
                onChange=(
                  event =>
                    _self.send(
                      UpdateSchoolCityField(
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                )
              />
            </div>
          </div>
        </form>
        <div className="justify-content-center">
          <button
            className="btn btn-outline-primary"
            onClick=(_ => _self.send(CreateTraining))>
            (ReasonReact.string("Annuler"))
          </button>
          <button
            className="btn btn-outline-primary"
            onClick=(_ => _self.send(CreateTraining))>
            (ReasonReact.string("Envoyer"))
          </button>
        </div>
      </div>,
  };
};